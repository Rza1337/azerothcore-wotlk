#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "InstanceScript.h"

enum Spells
{
    SPELL_TENTACLE_SLAM = 6524,      // Earthquake (Amateur)
    SPELL_INK_CLOUD = 44198,         // Smoke Bomb
    SPELL_CALL_OF_THE_ABYSS = 59414, // Dark Surge
    SPELL_CRUSHING_MAW = 33661,      // Crush Armor
    SPELL_TIDAL_SURGE = 37405,       // Watery Grave
    SPELL_BERSERK = 27680            // Berserk (Enrage)
};

enum Events
{
    EVENT_TENTACLE_SLAM = 1,
    EVENT_INK_CLOUD,
    EVENT_CALL_OF_THE_ABYSS,
    EVENT_CRUSHING_MAW,
    EVENT_TIDAL_SURGE,
    EVENT_BERSERK
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

    struct boss_nzhalAI : public BossAI
    {
        boss_nzhalAI(Creature* creature) : BossAI(creature, DATA_GENERAL_DRAKKISATH) { }

        void Reset() override
        {
            _Reset();
            me->SetDisableGravity(true);
            me->SetCanFly(true);
            me->SetReactState(REACT_AGGRESSIVE);
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            _JustEngagedWith();
            Talk(SAY_AGGRO);
            events.ScheduleEvent(EVENT_TENTACLE_SLAM, 10000);
            events.ScheduleEvent(EVENT_TIDAL_SURGE, 15000);
            events.ScheduleEvent(EVENT_BERSERK, 600000); // 10 minutes
        }

        void JustDied(Unit* /*killer*/) override
        {
            _JustDied();
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
                    case EVENT_TENTACLE_SLAM:
                        DoCastAOE(SPELL_TENTACLE_SLAM);
                        events.ScheduleEvent(EVENT_TENTACLE_SLAM, 12000);
                        break;

                    case EVENT_TIDAL_SURGE:
                    {
                        std::list<Unit*> targetList;
                        SelectTargetList(targetList, 5, SELECT_TARGET_NEAREST, 100.0f);
                        if (!targetList.empty())
                        {
                            auto itr = targetList.begin();
                            std::advance(itr, urand(0, targetList.size() - 1)); // Pick random target
                            Unit* target = *itr;
                            if (target)
                            {
                                DoCast(target, SPELL_TIDAL_SURGE);
                            }
                        }
                        events.ScheduleEvent(EVENT_TIDAL_SURGE, 20000);
                        break;
                    }

                    case EVENT_BERSERK:
                        DoCast(me, SPELL_BERSERK);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_nzhalAI(creature);
    }
};

void AddSC_boss_nzhal()
{
    new boss_nzhal();
}
