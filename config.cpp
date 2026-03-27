class CfgMods
{
	class BulletHoles
	{
		type = "mod";
		dependencies[] = { "Game", "Mission" };
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = { "BulletHoles/scripts/3_Game" };
			};
			class missionScriptModule
			{
				value = "";
				files[] = { "BulletHoles/scripts/5_Mission" };
			};
		};
	};
};
class CfgPatches
{
	class BulletHoles
	{
		requiredAddons[] = {};
	};
};

class CfgVehicles
{
	class HouseNoDestruct;
	class BulletHole_Base : HouseNoDestruct
	{
		scope = 1;
		model = "BulletHoles\models\plane.p3d";
		hiddenSelections[] = {"face"};
	};

	class BulletHole_Enter_Hit_Concrete_1 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\concrete\Hit_Concrete_1_ca.paa" };
	};
	class BulletHole_Enter_Hit_Concrete_2 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\concrete\Hit_Concrete_2_ca.paa" };
	};
	class BulletHole_Enter_Hit_Concrete_3 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\concrete\Hit_Concrete_3_ca.paa" };
	};
	class BulletHole_Enter_Hit_Concrete_4 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\concrete\Hit_Concrete_4_ca.paa" };
	};
	class BulletHole_Enter_Hit_Concrete_5 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\concrete\Hit_Concrete_5_ca.paa" };
	};

	class BulletHole_Enter_Hit_Glass_1 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\glass\Hit_Glass_1_ca.paa" };
	};
	class BulletHole_Enter_Hit_Glass_2 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\glass\Hit_Glass_2_ca.paa" };
	};
	class BulletHole_Enter_Hit_Glass_3 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\glass\Hit_Glass_3_ca.paa" };
	};
	class BulletHole_Enter_Hit_Glass_4 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\glass\Hit_Glass_4_ca.paa" };
	};
	class BulletHole_Enter_Hit_Glass_5 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\glass\Hit_Glass_5_ca.paa" };
	};

	class BulletHole_Enter_Hit_Glass_Thin_1 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\glass\Hit_Glass_1_ca.paa" };
	};
	class BulletHole_Enter_Hit_Glass_Thin_2 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\glass\Hit_Glass_2_ca.paa" };
	};
	class BulletHole_Enter_Hit_Glass_Thin_3 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\glass\Hit_Glass_3_ca.paa" };
	};
	class BulletHole_Enter_Hit_Glass_Thin_4 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\glass\Hit_Glass_4_ca.paa" };
	};
	class BulletHole_Enter_Hit_Glass_Thin_5 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\glass\Hit_Glass_5_ca.paa" };
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

	class BulletHole_Enter_Hit_Plaster_1 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\plaster\Hit_Plaster_1_ca.paa" };
	};
	class BulletHole_Enter_Hit_Plaster_2 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\plaster\Hit_Plaster_2_ca.paa" };
	};
	class BulletHole_Enter_Hit_Plaster_3 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\plaster\Hit_Plaster_3_ca.paa" };
	};
	class BulletHole_Enter_Hit_Plaster_4 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\plaster\Hit_Plaster_4_ca.paa" };
	};
	class BulletHole_Enter_Hit_Plaster_5 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\plaster\Hit_Plaster_5_ca.paa" };
	};

	class BulletHole_Enter_Hit_Plastic_1 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\rubber\Hit_Rubber_1_ca.paa" };
	};
	class BulletHole_Enter_Hit_Plastic_2 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\rubber\Hit_Rubber_2_ca.paa" };
	};
	class BulletHole_Enter_Hit_Plastic_3 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\rubber\Hit_Rubber_3_ca.paa" };
	};
	class BulletHole_Enter_Hit_Plastic_4 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\rubber\Hit_Rubber_4_ca.paa" };
	};
	class BulletHole_Enter_Hit_Plastic_5 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\rubber\Hit_Rubber_5_ca.paa" };
	};

	class BulletHole_Enter_Hit_Rubber_1 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\rubber\Hit_Rubber_1_ca.paa" };
	};
	class BulletHole_Enter_Hit_Rubber_2 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\rubber\Hit_Rubber_2_ca.paa" };
	};
	class BulletHole_Enter_Hit_Rubber_3 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\rubber\Hit_Rubber_3_ca.paa" };
	};
	class BulletHole_Enter_Hit_Rubber_4 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\rubber\Hit_Rubber_4_ca.paa" };
	};
	class BulletHole_Enter_Hit_Rubber_5 : BulletHole_Base
	{
		hiddenSelectionsTextures[] = { "BulletHoles\textures\rubber\Hit_Rubber_5_ca.paa" };
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
};