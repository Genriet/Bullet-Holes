class CfgMods
{
	class BulletHoles
	{
		type = "mod";
		dependencies[] = { "Game", "World" };
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = { "BulletHoles/scripts/3_Game" };
			};
			class worldScriptModule
			{
				value = "";
				files[] = { "BulletHoles/scripts/4_World" };
			};
		};
	};
};
class CfgPatches
{
	class BulletHoles
	{
		requiredAddons[] = { "DZ_Scripts", "DZ_Data" };
	};
};

class CfgVehicles
{
	class HouseNoDestruct;
	class BulletHole_Base : HouseNoDestruct
	{
		scope = 1;
		model = "BulletHoles\plane.p3d";
		hiddenSelections[] = {"face"};
	};
	class BulletHole_Stop : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\enter_ca.paa" };
	};
	class BulletHole_Enter : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\enter_ca.paa" };
	};
	class BulletHole_Exit : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\exit_ca.paa" };
	};
	class BulletHole_Ricochet : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\ricochet_ca.paa" };
	};

	class BulletHole_Enter_Hit_Wood_1 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\wood\Hit_Wood_1_ca.paa" };
	};
	class BulletHole_Enter_Hit_Wood_2 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\wood\Hit_Wood_2_ca.paa" };
	};
	class BulletHole_Enter_Hit_Wood_3 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\wood\Hit_Wood_3_ca.paa" };
	};
	class BulletHole_Enter_Hit_Wood_4 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\wood\Hit_Wood_4_ca.paa" };
	};
	class BulletHole_Enter_Hit_Wood_5 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\wood\Hit_Wood_5_ca.paa" };
	};

	class BulletHole_Enter_Hit_Textile_1 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\textile\Hit_Textile_1_ca.paa" };
	};
	class BulletHole_Enter_Hit_Textile_2 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\textile\Hit_Textile_2_ca.paa" };
	};
	class BulletHole_Enter_Hit_Textile_3 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\textile\Hit_Textile_3_ca.paa" };
	};
	class BulletHole_Enter_Hit_Textile_4 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\textile\Hit_Textile_4_ca.paa" };
	};
	class BulletHole_Enter_Hit_Textile_5 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\textile\Hit_Textile_5_ca.paa" };
	};

	class BulletHole_Enter_Hit_Metal_1 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\metal\Hit_Metal_1_ca.paa" };
	};
	class BulletHole_Enter_Hit_Metal_2 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\metal\Hit_Metal_2_ca.paa" };
	};
	class BulletHole_Enter_Hit_Metal_3 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\metal\Hit_Metal_3_ca.paa" };
	};
	class BulletHole_Enter_Hit_Metal_4 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\metal\Hit_Metal_4_ca.paa" };
	};
	class BulletHole_Enter_Hit_Metal_5 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\metal\Hit_Metal_5_ca.paa" };
	};
};