class BulletHoles_Config
{
	bool Enabled = true;
	bool ClientOnly = true;
	bool PrintDebug = false;

	float NormalOffset = 0.015; // Small offset to prevent z-fighting

	bool BulletEnterDecals = true;
	bool BulletExitDecals = false;
	bool BulletStopDecals = false;
	bool BulletRicochetDecals = false;

	bool MeleeDecals = false;

	bool ExplosionDecals = false;

	int GlobalMaxLimit = -1; // Max total decals in the world
	int GlobalMaxTime = -1; // Seconds before auto-delete
	int LimitPerObject = -1; // Max decals per single object

	ref TStringArray IgnoreSurfaces = {
		"Hit_Grass",
		"Hit_Dirt",
		"Hit_Sand",
		"Hit_Gravel",
		"Hit_Snow",
		"Hit_Foliage",
		"Hit_Foliage_Green",
		"Hit_Foliage_Conifer",
		"Hit_MeatBones",
		"Hit_Undefined",
		"Hit_ErrorNoMaterial"
	};
	ref TStringArray IgnoreObjects = {
		"CarScript" // Don't wanna deal with despawning decals when windows break completely.
		"CarDoor" // Same as above and decals don't attach properly to any animated part, no idea why, don't wanna deal with it right now.
	};

	int VariantsPerSurface = 5; // Number of texture variants per surface type
};

modded class DayZGame
{
	protected ref BulletHoles_Config m_BulletHoles_Config;

	protected ref array<EntityAI> m_BulletHoles_SpawnedDecalsArray = {};
	protected ref map<Object, ref array<EntityAI>> m_BulletHoles_SpawnedDecalsPerObject = new map<Object, ref array<EntityAI>>;

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

#ifndef SERVER
	override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, target, rpc_type, ctx);

		if (rpc_type == 5839759753957394)
		{
			Param1 <ref BulletHoles_Config> config;
			if (!ctx.Read(config)) return;
			m_BulletHoles_Config = config.param1;
		}
	}
#endif

	override void FirearmEffects(Object source, Object directHit, int componentIndex, string surface, vector pos, vector surfNormal, vector exitPos, vector inSpeed, vector outSpeed, bool isWater, bool deflected, string ammoType)
	{
		super.FirearmEffects(source, directHit, componentIndex, surface, pos, surfNormal, exitPos, inSpeed, outSpeed, isWater, deflected, ammoType);

		if (m_BulletHoles_Config.Enabled)
		{
			if ((IsClient() && m_BulletHoles_Config.ClientOnly) || (IsServer() && !m_BulletHoles_Config.ClientOnly))
			{
				BulletHoles_DetermineBulletDecalType(directHit, componentIndex, surface, pos, surfNormal, exitPos, inSpeed, outSpeed, isWater, deflected, ammoType);
			}
		}
	}

	void BulletHoles_DetermineBulletDecalType(Object target, int componentIndex, string surface, vector pos, vector surfNormal, vector exitPos, vector inSpeed, vector outSpeed, bool isWater, bool deflected, string ammoType)
	{
		if (!isWater && !BulletHoles_IsIgnoredSurface(surface) && !BulletHoles_IsIgnoredObject(target))
		{
			if (deflected && m_BulletHoles_Config.BulletRicochetDecals)
			{
				BulletHoles_SpawnDecal(surface, "Ricochet", target, componentIndex, pos, surfNormal, true, inSpeed);
			}
			else if (outSpeed != vector.Zero) 
			{
				if (m_BulletHoles_Config.BulletEnterDecals)
				{
					BulletHoles_SpawnDecal(surface, "Enter", target, componentIndex, pos, surfNormal);
				}
				if (m_BulletHoles_Config.BulletExitDecals)
				{
					BulletHoles_SpawnDecal(surface, "Exit", target, componentIndex, exitPos, -surfNormal);
				}
			}
			else
			{
				if (m_BulletHoles_Config.BulletStopDecals)
				{
					BulletHoles_SpawnDecal(surface, "Stop", target, componentIndex, pos, surfNormal);
				}
				else
				{
					BulletHoles_SpawnDecal(surface, "Enter", target, componentIndex, pos, surfNormal);
				}
			}
		}
	}

	// Disabled, waiting on BI fix https://feedback.bistudio.com/T192014
	/*override void CloseCombatEffects(Object source, Object directHit, int componentIndex, string surface, vector pos, vector surfNormal, bool isWater, string ammoType)
	{
		super.CloseCombatEffects(source, directHit, componentIndex, surface, pos, surfNormal, isWater, ammoType);
		if (m_BulletHoles_Config.Enabled)
		{
			if ((IsClient() && m_BulletHoles_Config.ClientOnly) || (IsServer() && !m_BulletHoles_Config.ClientOnly))
			{
				BulletHoles_DetermineMeleeDecalType(directHit, componentIndex, surface, pos, surfNormal, isWater, ammoType);
			}
		}
	}*/

	void BulletHoles_DetermineMeleeDecalType(Object target, int componentIndex, string surface, vector pos, vector surfNormal, bool isWater, string ammoType)
	{
		if (!isWater && !BulletHoles_IsIgnoredSurface(surface) && !BulletHoles_IsIgnoredObject(target) && m_BulletHoles_Config.MeleeDecals)
		{
			if (ammoType.Contains("Sharp"))
			{
				BulletHoles_SpawnDecal(surface, "MeleeSharp", target, componentIndex, pos, surfNormal);
			}
			else
			{
				BulletHoles_SpawnDecal(surface, "MeleeBlunt", target, componentIndex, pos, surfNormal);
			}
		}
	}

	bool BulletHoles_IsIgnoredSurface(string surface)
	{
		return m_BulletHoles_Config.IgnoreSurfaces.Find(surface) != -1;
	}

	bool BulletHoles_IsIgnoredObject(Object object)
	{
		foreach (string ignored : m_BulletHoles_Config.IgnoreObjects)
		{
			if (object.IsInherited(ignored.ToType()))
			{
				return true;
			}
		}
		return false;
	}

	void BulletHoles_SpawnDecal(string surface, string impact, Object target, int componentIndex, vector pos, vector normal, bool deflected = false, vector inSpeed = vector.Zero)
	{
		string type = string.Format("BulletHole_%1_%2_%3", impact, surface, Math.RandomIntInclusive(1, m_BulletHoles_Config.VariantsPerSurface));
		
		if (m_BulletHoles_Config.PrintDebug)
		{
			Print(string.Format("[BulletHoles] Spawning decal of type %1 at position %2", type, pos));
		}

		vector spawnNormal = normal.Normalized();
		vector SpawnPos = pos + spawnNormal * m_BulletHoles_Config.NormalOffset;

		EntityAI decal = EntityAI.Cast(GetGame().CreateObject(type, SpawnPos, IsClient()));

		if (!decal)
		{
			if (m_BulletHoles_Config.PrintDebug)
			{
				ErrorEx(string.Format("[BulletHoles] Failed to create decal of type %1, check if the type exists", type));
			}
			return;
		}

		decal.SetDirection(spawnNormal);
		vector ori = decal.GetOrientation();
		if (deflected)
		{
			// Not implemented, wanted to give ricochets a unique texture and rotation based on incoming bullet angle, but finding normal textures was hard enough already, maybe in the future.
		}
		else
		{
			// Random roll for visual variety
			ori[2] = Math.RandomIntInclusive(0, 360);
		}
		decal.SetOrientation(ori);

		if (target)
		{
			BulletHoles_AttachDecalToObject(decal, target, componentIndex);
			BulletHoles_ManagePerObjectLimit(target, decal);
		}

		BulletHoles_ManageGlobalLimit(decal);
		BulletHoles_ManageGlobalTimeLimit(decal);
	}

	void BulletHoles_AttachDecalToObject(EntityAI decal, Object target, int componentIndex)
	{
		int pivot = target.GetBonePivot(target.GetFireGeometryLevel(), componentIndex);
		vector parentMat[4], decalMat[4];

		if (pivot == -1) 
		{
			target.GetTransform(parentMat);
		}
		else
		{
			target.GetBoneTransformWS(pivot, parentMat);
		}

		float scale = target.GetScale();
		scale = 1.0 / (scale * scale);

		decal.GetTransform(decalMat);
		Math3D.MatrixInvMultiply4(parentMat, decalMat, decalMat);
		Math3D.MatrixOrthogonalize4(decalMat);
		decalMat[3] = decalMat[3] * scale;

		decal.SetTransform(decalMat);
		target.AddChild(decal, pivot);
	}

	void BulletHoles_ManageGlobalLimit(EntityAI newDecal)
	{
		m_BulletHoles_SpawnedDecalsArray.Insert(newDecal);

		if (m_BulletHoles_Config.GlobalMaxLimit > -1 && m_BulletHoles_SpawnedDecalsArray.Count() >= m_BulletHoles_Config.GlobalMaxLimit)
		{
			int oldestIndex = m_BulletHoles_SpawnedDecalsArray.Count() - m_BulletHoles_Config.GlobalMaxLimit;
			if (m_BulletHoles_SpawnedDecalsArray[oldestIndex])
			{
				m_BulletHoles_SpawnedDecalsArray[oldestIndex].DeleteSafe();
			}
		}
	}

	void BulletHoles_ManageGlobalTimeLimit(EntityAI newDecal)
	{
		if (m_BulletHoles_Config.GlobalMaxTime > -1)
		{
			GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLaterByName(newDecal, "DeleteSafe", m_BulletHoles_Config.GlobalMaxTime * 1000);
		}
	}

	void BulletHoles_ManagePerObjectLimit(Object target, EntityAI newDecal)
	{
		array<EntityAI> decals = m_BulletHoles_SpawnedDecalsPerObject.Get(target);

		if (decals)
		{
			decals.Insert(newDecal);
			if (m_BulletHoles_Config.LimitPerObject > -1 && decals.Count() > m_BulletHoles_Config.LimitPerObject)
			{
				int oldestIndex = decals.Count() - m_BulletHoles_Config.LimitPerObject;
				if (decals[oldestIndex])
				{
					decals[oldestIndex].DeleteSafe();
				}
			}
		}
		else
		{
			array<EntityAI> arr = { newDecal };
			m_BulletHoles_SpawnedDecalsPerObject.Set(target, arr);
		}
	}
};