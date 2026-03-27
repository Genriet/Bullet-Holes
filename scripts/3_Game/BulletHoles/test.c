class BulletHoles_Config
{
	bool ClientOnly = true;
	float NormalOffset = 0.015;
	bool BulletDecals = true;
	bool MeleeDecals = false;
	bool ExplosionDecals = false;
	int GlobalMaxLimit = -1;
	int GlobalMaxTime = -1;
	int LimitPerObject = -1;
	ref TStringArray IgnoreSurfaces = {
		"Hit_Grass",
		"Hit_Dirt",
		"Hit_Sand",
		"Hit_Gravel",
		"Hit_Snow",
		"Hit_Foliage",
		"Hit_Foliage_Green",
		"Hit_Foliage_Conifer",
		"Hit_Glass",
		"Hit_Glass_Thin",
		"Hit_MeatBones",
		"Hit_Undefined",
		"Hit_ErrorNoMaterial"
	};
};

modded class DayZGame
{
	protected ref BulletHoles_Config m_BulletHoles_Config;

	protected ref array<EntityAI> m_BulletHoles_SpawnedDecalsArray = {};
	protected ref map<Object, ref array<EntityAI>> m_BulletHoles_SpawnedDecalsPerObjectMap = new map<Object, ref array<EntityAI>>;

	void DayZGame()
	{
		GetBulletHoles_Config();
	}

	BulletHoles_Config GetBulletHoles_Config()
	{
		if (!m_BulletHoles_Config)
		{
			if (!FileExist("$profile:\\BulletHoles"))
			{
				MakeDirectory("$profile:\\BulletHoles");
			}
			if (!FileExist("$profile:\\BulletHoles\\BulletHoles.json"))
			{
				m_BulletHoles_Config = new BulletHoles_Config;

				JsonFileLoader<BulletHoles_Config>.JsonSaveFile("$profile:\\BulletHoles\\BulletHoles.json", m_BulletHoles_Config);
			}
			else
			{
				JsonFileLoader<BulletHoles_Config>.JsonLoadFile("$profile:\\BulletHoles\\BulletHoles.json", m_BulletHoles_Config);

				if (!m_BulletHoles_Config)
				{
					m_BulletHoles_Config = new BulletHoles_Config;
					ErrorEx("BULLET HOLES JSON IS INVALID, USING DEFAULT ONE. REGENERATE JSON");
				}
			}
		}
		return m_BulletHoles_Config;
	}

	override void FirearmEffects(Object source, Object directHit, int componentIndex, string surface, vector pos, vector surfNormal, vector exitPos, vector inSpeed, vector outSpeed, bool isWater, bool deflected, string ammoType)
	{
		super.FirearmEffects(source, directHit, componentIndex, surface, pos, surfNormal, exitPos, inSpeed, outSpeed, isWater, deflected, ammoType);

		if ((IsClient() && m_BulletHoles_Config.ClientOnly) || (IsServer() && !m_BulletHoles_Config.ClientOnly))
		{
			if (m_BulletHoles_Config.BulletDecals && !isWater && !BulletHoles_IsIgnoredSurface(surface))
			{
				if (deflected)
				{
					BulletHoles_SpawnDecal(surface, "Ricochet", directHit, componentIndex, pos, surfNormal, true, inSpeed);
				}
				else if (outSpeed != vector.Zero) 
				{
					BulletHoles_SpawnDecal(surface, "Enter", directHit, componentIndex, pos, surfNormal);
					BulletHoles_SpawnDecal(surface, "Exit", directHit, componentIndex, exitPos, -surfNormal);
				}
				else
				{
					BulletHoles_SpawnDecal(surface, "Stop", directHit, componentIndex, pos, surfNormal);
				}
			}
		}
	}

	// Disabled, waiting on BI fix https://feedback.bistudio.com/T192014
	/*override void CloseCombatEffects(Object source, Object directHit, int componentIndex, string surface, vector pos, vector surfNormal, bool isWater, string ammoType)
	{
		super.CloseCombatEffects(source, directHit, componentIndex, surface, pos, surfNormal, isWater, ammoType);

		if ((IsClient() && m_BulletHoles_Config.ClientOnly) || (IsServer() && !m_BulletHoles_Config.ClientOnly))
		{
			if (m_BulletHoles_Config.MeleeDecals && !isWater && !BulletHoles_IsIgnoredSurface(surface))
			{
				if (ammoType.Contains("Sharp"))
					BulletHoles_SpawnDecal(surface, "MeleeSharp", directHit, componentIndex, pos, surfNormal);
				else
					BulletHoles_SpawnDecal(surface, "MeleeBlunt", directHit, componentIndex, pos, surfNormal);
			}
		}
	}*/

	bool BulletHoles_IsIgnoredSurface(string surface)
	{
		return m_BulletHoles_Config.IgnoreSurfaces.Find(surface) != -1;
	}

	void BulletHoles_SpawnDecal(string surface, string impact, Object target, int componentIndex, vector pos, vector normal, bool deflected = false, vector inSpeed = vector.Zero)
	{
		string type = string.Format("BulletHole_%1", impact/*, surface, Math.RandomIntInclusive(1, 5)*/);
		ChatPlayer(type);

		vector spawnNormal = normal.Normalized();
		vector offsetPos = pos + spawnNormal * m_BulletHoles_Config.NormalOffset;

		EntityAI decal = EntityAI.Cast(GetGame().CreateObject(type, offsetPos, IsClient()));
		if (!decal) return;

		decal.SetDirection(spawnNormal);
		vector ori = decal.GetOrientation();
		if (deflected)
		{
			//math
		}
		else
		{
			// Random rotation for normal hits
			ori[2] = Math.RandomIntInclusive(0, 360);
		}
		decal.SetOrientation(ori);

		if (target)
		{
			int pivot = target.GetBonePivot(target.GetFireGeometryLevel(), componentIndex);
			vector parentMat[4], decalMat[4];

			if (pivot == -1) target.GetTransform(parentMat);
			else target.GetBoneTransformWS(pivot, parentMat);

			float scale = target.GetScale();
			scale = 1.0 / (scale * scale);

			decal.GetTransform(decalMat);
			Math3D.MatrixInvMultiply4(parentMat, decalMat, decalMat);
			Math3D.MatrixOrthogonalize4(decalMat);
			decalMat[3] = decalMat[3] * scale;

			decal.SetTransform(decalMat);
			target.AddChild(decal, pivot);

			if (m_BulletHoles_Config.LimitPerObject > -1)
			{
				array<EntityAI> decals = m_BulletHoles_SpawnedDecalsPerObjectMap.Get(target);

				if (decals)
				{
					decals.Insert(decal);
					if (decals.Count() > m_BulletHoles_Config.LimitPerObject)
					{
						int oldestIndex1 = decals.Count() - m_BulletHoles_Config.LimitPerObject;
						if (decals[oldestIndex1])
							decals[oldestIndex1].DeleteSafe();
					}
				}
				else
				{
					array<EntityAI> arr = { decal };
					m_BulletHoles_SpawnedDecalsPerObjectMap.Set(target, arr);
				}
			}
		}

		if (m_BulletHoles_Config.GlobalMaxLimit > -1)
		{
			m_BulletHoles_SpawnedDecalsArray.Insert(decal);

			if (m_BulletHoles_SpawnedDecalsArray.Count() >= m_BulletHoles_Config.GlobalMaxLimit)
			{
				int oldestIndex = m_BulletHoles_SpawnedDecalsArray.Count() - m_BulletHoles_Config.GlobalMaxLimit;
				if (m_BulletHoles_SpawnedDecalsArray[oldestIndex])
					m_BulletHoles_SpawnedDecalsArray[oldestIndex].DeleteSafe();
			}
		}

		if (m_BulletHoles_Config.GlobalMaxTime > -1)
		{
			GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLaterByName(decal, "DeleteSafe", m_BulletHoles_Config.GlobalMaxTime * 1000);
		}
	}
};