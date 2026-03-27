modded class MissionServer
{
	
	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
    {
        super.InvokeOnConnect(player, identity);
        auto configParams = new Param1<ref BulletHoles_Config>(GetDayZGame().GetBulletHoles_Config());
        GetGame().RPCSingleParam(player, 5839759753957394, configParams, true, identity);
    }
};