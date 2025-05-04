#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "ruins_of_ahnqiraj.h"

enum Emotes
{
    EMOTE_TARGET              = 0,
    EMOTE_PHASE_2             = 1,
    EMOTE_PHASE_3             = 2,
    EMOTE_EGG_SPAWN           = 3,
    EMOTE_PLAYER_EXPLODE      = 4,
    EMOTE_MIND_CONTROL        = 5,
    EMOTE_DEATH               = 6
};

enum Spells
{
    SPELL_CRUSHING_BITE       = 26029,
    SPELL_TERROR_WAVE         = 28168,
    SPELL_THREAT_LOCK         = 28747,
    SPELL_TAUNT_IMMUNITY      = 31704,
    SPELL_HIVEMIND_ASSIMILATION = 80003,
    SPELL_HIVEMIND_AURA       = 34471, // Visual glow effect
    SPELL_MIND_CONTROL_HIVEMIND = 80006,
    SPELL_EXPLODE_ON_DISPEL   = 80007
};

enum Events
{
    EVENT_CRUSHING_BITE       = 1,
    EVENT_TERROR_WAVE         = 2,
    EVENT_TARGET_SWAP         = 3,
    EVENT_SUMMON_EGGS         = 4,
    EVENT_HATCH_EGGS          = 5,
    EVENT_HIVEMIND_ASSIMILATION = 6,
    EVENT_BERSERK_PHASE       = 7
};

struct boss_kaashzul : public BossAI
{
    boss_kaashzul(Creature* creature) : BossAI(creature, DATA_BURU) {}

    void EnterCombat(Unit* /*who*/) override
    {
        Talk(EMOTE_TARGET);
        DoCastSelf(SPELL_TAUNT_IMMUNITY, true);
        events.ScheduleEvent(EVENT_CRUSHING_BITE, 7s);
        events.ScheduleEvent(EVENT_TARGET_SWAP, 30s);
    }

    void StartSummoningPhase()
    {
        Talk(EMOTE_PHASE_2);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        events.Reset();

        for (uint8 i = 0; i < 5; ++i)
        {
            Position eggSpawn;
            me->GetRandomNearPosition(eggSpawn, 10.0f);
            if (GameObject* egg = me->SummonGameObject(GO_QIRAJI_EGG, eggSpawn, 0, 0, 0, 0, 60))
            {
                eggList.push_back(egg);
            }
        }

        events.ScheduleEvent(EVENT_HATCH_EGGS, 8s);
        events.ScheduleEvent(EVENT_HIVEMIND_ASSIMILATION, 15s);
    }

    void HatchEggs()
    {
        for (GameObject* egg : eggList)
        {
            if (!egg->IsInWorld())
                continue;

            egg->Delete();

            Position spawnPos = egg->GetPosition();
            if (Creature* spawnedTrash = me->SummonCreature(NPC_HATCHED_TRASH, spawnPos, TEMPSUMMON_CORPSE_DESPAWN, 30000))
            {
                spawnedTrash->SetInCombatWithZone();
            }
        }

        eggList.clear();
        events.ScheduleEvent(EVENT_HATCH_EGGS, 10s);
    }

    void OnAuraRemoved(Unit* target, uint32 spellId, AuraRemoveMode mode) override
    {
        if (spellId == SPELL_HIVEMIND_ASSIMILATION && mode == AURA_REMOVE_EXPIRE)
        {
            Talk(EMOTE_MIND_CONTROL, target);
            DoCast(target, SPELL_MIND_CONTROL_HIVEMIND);
            DoCast(target, SPELL_EXPLODE_ON_DISPEL);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_CRUSHING_BITE:
                    DoCastVictim(SPELL_CRUSHING_BITE);
                    events.ScheduleEvent(EVENT_CRUSHING_BITE, 8s);
                    break;
                case EVENT_TERROR_WAVE:
                    DoCastAOE(SPELL_TERROR_WAVE);
                    events.ScheduleEvent(EVENT_TERROR_WAVE, 18s);
                    break;
                case EVENT_TARGET_SWAP:
                    SelectNewTarget();
                    break;
                case EVENT_SUMMON_EGGS:
                    StartSummoningPhase();
                    break;
                case EVENT_HATCH_EGGS:
                    HatchEggs();
                    break;
                case EVENT_HIVEMIND_ASSIMILATION:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                    {
                        DoCast(target, SPELL_HIVEMIND_ASSIMILATION);
                        DoCast(target, SPELL_HIVEMIND_AURA);
                        Talk(EMOTE_MIND_CONTROL, target);
                    }
                    events.ScheduleEvent(EVENT_HIVEMIND_ASSIMILATION, 15s);
                    break;
                default:
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }

private:
    std::vector<GameObject*> eggList;
};

struct npc_mind_controlled_player : public ScriptedAI
{
    npc_mind_controlled_player(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        me->SetReactState(REACT_AGGRESSIVE);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        events.ScheduleEvent(EVENT_ATTACK_RANDOM, 2s);
    }

    void UpdateAI(uint32 diff) override
    {
        events.Update(diff);

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_ATTACK_RANDOM:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                    {
                        if (me->GetClass() == CLASS_WARRIOR)
                            DoCast(target, SPELL_BERSERKER_STRIKE);
                        else if (me->GetClass() == CLASS_MAGE)
                            DoCast(target, SPELL_ARCANE_BLAST);
                        else if (me->GetClass() == CLASS_PRIEST)
                            DoCast(target, SPELL_MIND_FLAY);
                    }
                    events.ScheduleEvent(EVENT_ATTACK_RANDOM, 3s);
                    break;
            }
        }
    }
};

void AddSC_boss_kaashzul()
{
    RegisterRuinsOfAhnQirajCreatureAI(boss_kaashzul);
    RegisterRuinsOfAhnQirajCreatureAI(npc_mind_controlled_player);
}
