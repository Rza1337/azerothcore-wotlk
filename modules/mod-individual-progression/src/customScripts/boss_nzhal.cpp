#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Player.h"

enum Spells
{
    SPELL_TENTACLE_SLAM = 6524,      // Earthquake (Amateur)
    SPELL_INK_CLOUD = 44198,         // Smoke Bomb
    SPELL_CALL_OF_THE_ABYSS = 59414, // Dark Surge
    SPELL_CRUSHING_MAW = 33661,      // Crush Armor
    SPELL_TIDAL_SURGE = 37405,       // Watery Grave
    SPELL_BERSERK = 27680            // Berserk (Enrage)
};

enum Texts
{
    SAY_AGGRO = 0,
    SAY_DEATH = 1
};

class boss_nzhal : public CreatureScript
{
public:
    boss_nzhal() : CreatureScript("boss_nzhal") { }

    struct boss_nzhalAI : public ScriptedAI
    {
        boss_nzhalAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            me->SetDisableGravity(true);
            me->SetCanFly(true);
            me->SetReactState(REACT_AGGRESSIVE);
        }

        void JustEngagedWith(Unit* who) override
        {
            Talk(SAY_AGGRO);
            events.ScheduleEvent(1, 10000); // Tentacle Slam
            events.ScheduleEvent(2, 15000); // Tidal Surge
            events.ScheduleEvent(3, 600000); // Berserk (10-minute enrage)
        }

        void JustDied(Unit* /*killer*/) override
        {
            Talk(SAY_DEATH);
        }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case 1: // Tentacle Slam
                    DoCastAOE(SPELL_TENTACLE_SLAM);
                    events.ScheduleEvent(1, 12000);
                    break;

                case 2: // Tidal Surge
                {
                    std::list<Unit*> targetList;
                    SelectTargetList(targetList, 10, SELECT_TARGET_NEAREST, 100.0f); // Get up to 10 targets
                    if (!targetList.empty())
                    {
                        auto itr = targetList.begin();
                        std::advance(itr, urand(0, targetList.size() - 1)); // Pick a random target
                        Unit* target = *itr;
                        if (target)
                        {
                            DoCast(target, SPELL_TIDAL_SURGE);
                        }
                    }
                    events.ScheduleEvent(2, 20000);
                    break;
                }

                case 3: // Berserk
                    DoCast(me, SPELL_BERSERK);
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_nzhalAI(creature);
    }
};


void AddSC_boss_nzhal()
{
    new boss_nzhal();
}