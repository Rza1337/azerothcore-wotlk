#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "Player.h"

class npc_wave_portal : public CreatureScript
{
public:
    npc_wave_portal() : CreatureScript("npc_wave_portal") { }

    struct npc_wave_portalAI : public ScriptedAI
    {
        npc_wave_portalAI(Creature* creature) : ScriptedAI(creature) { }
    };

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Enter the Trial of Strength", GOSSIP_SENDER_MAIN, 1);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        if (action == 1)
        {
            player->CLOSE_GOSSIP_MENU();

            float x = 597.0f;
            float y = -187.0f;
            float z = -51.0f;
            float o = 3.14f;

            player->TeleportTo(230, x, y, z, o); // Map 230 is Blackrock Depths

            return true;
        }

        return false;
    }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_wave_portalAI(creature);
    }
};

void AddSC_npc_wave_portal()
{
    new npc_wave_portal();
}
