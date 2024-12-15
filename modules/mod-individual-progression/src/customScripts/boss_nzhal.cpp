/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "InstanceScript.h"

enum Spells
{
    SPELL_TENTACLE_SLAM = 6524,      // Earthquake (Amateur)
    SPELL_INK_CLOUD = 44198,         // Smoke Bomb
    SPELL_CALL_OF_THE_ABYSS = 59414, // Dark Surge
    SPELL_CRUSHING_MAW = 33661,      // Crush Armor
    SPELL_DROWNING_DEPTHS = 55964,   // Choking Breath (stacking debuff)
    SPELL_TIDAL_SURGE = 37405,       // Watery Grave
    SPELL_BERSERK = 27680            // Berserk (enrage)
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
    SAY_DEATH = 1,
    SAY_PULL = 2
};

class boss_nzhal : public CreatureScript
{
public:
    boss_nzhal() : CreatureScript("boss_nzhal") { }

    struct boss_nzhalAI : public ScriptedAI
    {
        boss_nzhalAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        void Reset() override
        {
            events.Reset();
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetDisableGravity(true); // Remain at the bottom of the water pit
            me->SetSwimming(true);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            Talk(SAY_AGGRO, "You dare disturb the Maw of Eternity?");
            events.ScheduleEvent(EVENT_TENTACLE_SLAM, 10000);
            events.ScheduleEvent(EVENT_INK_CLOUD, 30000);
            events.ScheduleEvent(EVENT_CALL_OF_THE_ABYSS, 20000);
            events.ScheduleEvent(EVENT_CRUSHING_MAW, 8000);
            events.ScheduleEvent(EVENT_TIDAL_SURGE, 15000);
            events.ScheduleEvent(EVENT_BERSERK, 600000); // 10 minutes
        }

        void JustDied(Unit* /*killer*/) override
        {
            Talk(SAY_DEATH, "The abyss... will consume you all...");
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
                    case EVENT_INK_CLOUD:
                        DoCastAOE(SPELL_INK_CLOUD);
                        events.ScheduleEvent(EVENT_INK_CLOUD, 30000);
                        break;
                    case EVENT_CALL_OF_THE_ABYSS:
                        Talk(SAY_PULL, "The depths will consume you!");
                        DoCastAOE(SPELL_CALL_OF_THE_ABYSS);
                        events.ScheduleEvent(EVENT_CALL_OF_THE_ABYSS, 20000 + urand(0, 10000));
                        break;
                    case EVENT_CRUSHING_MAW:
                        if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                            DoCast(target, SPELL_CRUSHING_MAW);
                        events.ScheduleEvent(EVENT_CRUSHING_MAW, 8000);
                        break;
                    case EVENT_TIDAL_SURGE:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                            DoCast(target, SPELL_TIDAL_SURGE);
                        events.ScheduleEvent(EVENT_TIDAL_SURGE, 15000);
                        break;
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
