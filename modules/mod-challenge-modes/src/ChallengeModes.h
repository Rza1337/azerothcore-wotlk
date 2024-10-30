#ifndef CHALLENGEMODES_H
#define CHALLENGEMODES_H

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Item.h"
#include "ItemTemplate.h"
#include "GameObjectAI.h"
#include "Pet.h"
#include <map>
#include <unordered_map>

enum ChallengeModeSettings
{
    SETTING_HARDCORE           = 0,
    SETTING_SEMI_HARDCORE      = 1,
    SETTING_SELF_CRAFTED       = 2,
    SETTING_ITEM_QUALITY_LEVEL = 3,
    SETTING_SLOW_XP_GAIN       = 4,
    SETTING_VERY_SLOW_XP_GAIN  = 5,
    SETTING_QUEST_XP_ONLY      = 6,
    SETTING_IRON_MAN           = 7,
    HARDCORE_DEAD              = 8,
    SETTING_PACIFIST           = 9,
    SETTING_TURTLE_MODE        = 10,
    SETTING_QUESTLESS          = 11,
    SETTING_CASHLESS           = 12
};

enum AllowedProfessions
{
    RUNEFORGING    = 53428,
    POISONS        = 2842,
    BEAST_TRAINING = 5149
};

class ChallengeModes
{
public:
    static ChallengeModes* instance();

    bool challengesEnabled, hardcoreEnable, semiHardcoreEnable, selfCraftedEnable, itemQualityLevelEnable, slowXpGainEnable, verySlowXpGainEnable, turtleModeEnable, questXpOnlyEnable, ironManEnable, pacifistEnable, questlessEnable, cashlessEnable;
    uint32 hardcoreDisableLevel, semiHardcoreDisableLevel, selfCraftedDisableLevel, itemQualityLevelDisableLevel, slowXpGainDisableLevel, verySlowXpGainDisableLevel, turtleModeDisableLevel, questXpOnlyDisableLevel, ironManDisableLevel, pacifistDisableLevel, questlessDisableLevel, cashlessDisableLevel;
    uint32 hardcoreItemRewardAmount, semiHardcoreItemRewardAmount, selfCraftedItemRewardAmount, itemQualityLevelItemRewardAmount, slowXpGainItemRewardAmount, verySlowXpGainItemRewardAmount, turtleModeXpGainItemRewardAmount, questXpOnlyItemRewardAmount, ironManItemRewardAmount, pacifistItemRewardAmount, questlessItemRewardAmount, cashlessItemRewardAmount;
    float hardcoreXpBonus, semiHardcoreXpBonus, selfCraftedXpBonus, itemQualityLevelXpBonus, questXpOnlyXpBonus, slowXpGainBonus, verySlowXpGainBonus, turtleModeXpGainBonus, ironManXpBonus, pacifistXpBonus, questlessXpBonus, cashlessXpBonus;

    std::unordered_map<uint8, uint32> hardcoreTitleRewards, semiHardcoreTitleRewards, selfCraftedTitleRewards, itemQualityLevelTitleRewards, slowXpGainTitleRewards, verySlowXpGainTitleRewards, turtleModeXpGainTitleRewards, questXpOnlyTitleRewards, ironManTitleRewards, pacifistTitleRewards, questlessTitleRewards, cashlessTitleRewards;
    std::unordered_map<uint8, uint32> hardcoreItemRewards, semiHardcoreItemRewards, selfCraftedItemRewards, itemQualityLevelItemRewards, slowXpGainItemRewards, verySlowXpGainItemRewards, turtleModeXpGainItemRewards, questXpOnlyItemRewards, ironManItemRewards, pacifistItemRewards, questlessItemRewards, cashlessItemRewards;
    std::unordered_map<uint8, uint32> hardcoreTalentRewards, semiHardcoreTalentRewards, selfCraftedTalentRewards, itemQualityLevelTalentRewards, slowXpGainTalentRewards, verySlowXpGainTalentRewards, turtleModeXpGainTalentRewards, questXpOnlyTalentRewards, ironManTalentRewards, pacifistTalentRewards, questlessTalentRewards, cashlessTalentRewards;
    std::unordered_map<uint8, uint32> hardcoreAchievementReward, semiHardcoreAchievementReward, selfCraftedAchievementReward, itemQualityLevelAchievementReward, slowXpGainAchievementReward, verySlowXpGainAchievementReward, turtleModeXpGainAchievementReward, questXpOnlyAchievementReward, ironManAchievementReward, pacifistAchievementReward, questlessAchievementReward, cashlessAchievementReward;

    std::unordered_map<std::string, std::unordered_map<uint8, uint32>*> rewardConfigMap =
    {
        { "Hardcore.TitleRewards",                &hardcoreTitleRewards                 },
        { "SemiHardcore.TitleRewards",            &semiHardcoreTitleRewards             },
        { "SelfCrafted.TitleRewards",             &selfCraftedTitleRewards              },
        { "ItemQualityLevel.TitleRewards",        &itemQualityLevelTitleRewards         },
        { "SlowXpGain.TitleRewards",              &slowXpGainTitleRewards               },
        { "VerySlowXpGain.TitleRewards",          &verySlowXpGainTitleRewards           },
        { "QuestXpOnly.TitleRewards",             &questXpOnlyTitleRewards              },
        { "IronMan.TitleRewards",                 &ironManTitleRewards                  },
        { "Pacifist.TitleRewards",                &pacifistTitleRewards                 }, 
        { "TurtleMode.TitleRewards",              &turtleModeXpGainTitleRewards         },
        { "Questless.TitleRewards",               &questlessTitleRewards                },
        { "Cashless.TitleRewards",                &cashlessTitleRewards                 },

        { "Hardcore.TalentRewards",               &hardcoreTalentRewards                },
        { "SemiHardcore.TalentRewards",           &semiHardcoreTalentRewards            },
        { "SelfCrafted.TalentRewards",            &selfCraftedTalentRewards             },
        { "ItemQualityLevel.TalentRewards",       &itemQualityLevelTalentRewards        },
        { "SlowXpGain.TalentRewards",             &slowXpGainTalentRewards              },
        { "VerySlowXpGain.TalentRewards",         &verySlowXpGainTalentRewards          },
        { "QuestXpOnly.TalentRewards",            &questXpOnlyTalentRewards             },
        { "IronMan.TalentRewards",                &ironManTalentRewards                 },
        { "Pacifist.TalentRewards",               &pacifistTalentRewards                },
        { "TurtleMode.TalentRewards",             &turtleModeXpGainTalentRewards        },
        { "Questless.TalentRewards",              &questlessTalentRewards               },
        { "Cashless.TalentRewards",               &cashlessTalentRewards                },

        { "Hardcore.ItemRewards",                 &hardcoreItemRewards                  },
        { "SemiHardcore.ItemRewards",             &semiHardcoreItemRewards              },
        { "SelfCrafted.ItemRewards",              &selfCraftedItemRewards               }, 
        { "ItemQualityLevel.ItemRewards",         &itemQualityLevelItemRewards          },
        { "SlowXpGain.ItemRewards",               &slowXpGainItemRewards                },
        { "VerySlowXpGain.ItemRewards",           &verySlowXpGainItemRewards            },
        { "QuestXpOnly.ItemRewards",              &questXpOnlyItemRewards               },
        { "IronMan.ItemRewards",                  &ironManItemRewards                   },
        { "Pacifist.ItemRewards",                 &pacifistItemRewards                  }, 
        { "TurtleMode.ItemRewards",               &turtleModeXpGainItemRewards          },
        { "Questless.ItemRewards",                &questlessItemRewards                 },
        { "Cashless.ItemRewards",                 &cashlessItemRewards                  },

        { "Hardcore.AchievementReward",           &hardcoreAchievementReward            },
        { "SemiHardcore.AchievementReward",       &semiHardcoreAchievementReward        },
        { "SelfCrafted.AchievementReward",        &selfCraftedAchievementReward         },
        { "ItemQualityLevel.AchievementReward",   &itemQualityLevelAchievementReward    },
        { "SlowXpGain.AchievementReward",         &slowXpGainAchievementReward          },
        { "VerySlowXpGain.AchievementReward",     &verySlowXpGainAchievementReward      },
        { "QuestXpOnly.AchievementReward",        &questXpOnlyAchievementReward         },
        { "IronMan.AchievementReward",            &ironManAchievementReward             },
        { "Pacifist.AchievementReward",           &pacifistAchievementReward            },
        { "TurtleMode.AchievementReward",         &turtleModeXpGainAchievementReward    },
        { "Questless.AchievementReward",          &questlessAchievementReward           },
        { "Cashless.AchievementReward",           &cashlessAchievementReward            }
    };

    [[nodiscard]] bool enabled() const { return challengesEnabled; }
    [[nodiscard]] bool challengeEnabled(ChallengeModeSettings setting) const;
    [[nodiscard]] uint32 getDisableLevel(ChallengeModeSettings setting) const;
    [[nodiscard]] float getXpBonusForChallenge(ChallengeModeSettings setting) const;
    bool challengeEnabledForPlayer(ChallengeModeSettings setting, Player* player) const;
    [[nodiscard]] const std::unordered_map<uint8, uint32> *getTitleMapForChallenge(ChallengeModeSettings setting) const;
    [[nodiscard]] const std::unordered_map<uint8, uint32> *getTalentMapForChallenge(ChallengeModeSettings setting) const;
    [[nodiscard]] const std::unordered_map<uint8, uint32> *getItemMapForChallenge(ChallengeModeSettings setting) const;
    [[nodiscard]] const std::unordered_map<uint8, uint32> *getAchievementMapForChallenge(ChallengeModeSettings setting) const;
    [[nodiscard]] uint32 getItemRewardAmount(ChallengeModeSettings setting) const;
    void LearnSpellsForNewLevel(Player* player, uint8 fromLevel);
    uint32 GetSpellFamily(const Player* p);
    void ApplyAdditionalSpells(uint8 level, uint32 playerSpellFamily, Player* player);
    bool IsIgnoredSpell(uint32 spellID);

    private:
        std::unordered_set<uint32> m_ignoreSpells =
        {
            64380, 23885, 23880, 44461, 25346, 10274, 10273, 8418,  8419,  7270,  7269,  7268,  54648, 12536, 24530, 70909, 12494, 57933, 24224, 27095, 27096, 27097, 27099, 32841, 56131, 56160, 56161, 48153, 34754, 64844, 64904, 48085, 33110, 48084,
            28276, 27874, 27873, 7001,  49821, 53022, 47757, 47750, 47758, 47666, 53001, 52983, 52998, 52986, 52987, 52999, 52984, 53002, 53003, 53000, 52988, 52985, 42208, 42209, 42210, 42211, 42212, 42213, 42198, 42937, 42938, 12484, 12485, 12486,
            44461, 55361, 55362, 34913, 43043, 43044, 38703, 38700, 27076, 42844, 42845, 64891, 25912, 25914, 25911, 25913, 25902, 25903, 27175, 27176, 33073, 33074, 48822, 48820, 48823, 48821, 20154, 25997, 20467, 20425, 67,    26017, 34471, 53254,
            13812, 14314, 14315, 27026, 49064, 49065, 60202, 60210, 13797, 14298, 14299, 14300, 14301, 27024, 49053, 49054, 52399, 1742,  24453, 53548, 53562, 52016, 26064, 35346, 57386, 57389, 57390, 57391, 57392, 57393, 55509, 35886, 43339, 45297,
            45298, 45299, 45300, 45301, 45302, 49268, 49269, 8349,  8502,  8503,  11306, 11307, 25535, 25537, 61650, 61654, 63685, 45284, 45286, 45287, 45288, 45289, 45290, 45291, 45292, 45293, 45294, 45295, 45296, 49239, 49240, 26364, 26365, 26366,
            26367, 26369, 26370, 26363, 26371, 26372, 49278, 49279, 32176, 32175, 21169, 47206, 27285, 47833, 47836, 42223, 42224, 42225, 42226, 42218, 47817, 47818, 42231, 42232, 42233, 42230, 48466, 44203, 44205, 44206, 44207, 44208, 48444, 48445,
            33891, 52374, 57532, 59921, 52372, 49142, 52375, 47633, 47632, 52373, 50536, 27214, 47822, 11682, 11681, 5857,  1010,  24907, 24905, 53227, 61391, 61390, 61388, 61387, 64801, 5421,  9635,  1178,  20186, 20185, 20184, 20187, 25899, 24406,
            50581, 30708, 48076, 62900, 62901, 62902, 59671, 50589, 66906, 66907, 24131, 23455, 23458, 23459, 27803, 27804, 27805, 25329, 48075, 42243, 42244, 42245, 42234, 58432, 58433, 65878, 18848, 16979, 49376, 54055, 20647, 42243, 24131, 45470,
            31898, 31804, 53733, 31803, 53742, 53725, 53726, 1804, 348, 1455, 1456, 11687, 11688, 11689, 27222, 57946, 25306, 53652, 53653, 53654, 7328, 10322, 10324, 20772, 20773, 48949, 48950, 33878, 33876, 33982, 33986, 33987, 33983, 48563, 48565,
            48566, 48564,

            //Dalaran Brilliance and Dalaran Intellect mage class as they are spells purchased in Dalaran with limited sales by NPCs
            61316,61024,
            
            // COSMETIC SPELLS
            28271, 28272, 61025, 61305, 61721, 61780,

            // OPTIONAL QUEST SPELLS
            18540,
        };

        struct AddSpell // Additional Spell Entry
        {
            uint32 spellId;
            TeamId faction = TeamId::TEAM_NEUTRAL;
        
        };

         // { level: { SPELL_FAMILY_NAME: [{ spellId: uint32, faction: TeamId }] } }
        using SpellFamilyToExtraSpells = std::unordered_map<uint32, std::vector<AddSpell>>;
        using AdditionalSpellsList = std::unordered_map<uint8, SpellFamilyToExtraSpells>;
         // -------------------------------------------- ^^^^^ level

    AdditionalSpellsList m_additionalSpells =
    {
        {3,
        {
            {SPELLFAMILY_WARLOCK,
            {
                AddSpell{348}, // Immolate
            }},
        }},
        {6,
        {
            {SPELLFAMILY_WARRIOR,
            {
                AddSpell{3127}, // parry
            }},
        }},
        {8,
        {
            {SPELLFAMILY_HUNTER,
            {
                AddSpell{3127}, // parry
            }},
            {SPELLFAMILY_PALADIN,
            {
                AddSpell{3127}, // parry
            }},
        }},
        {10,
        {
            {SPELLFAMILY_HUNTER,
            {
                AddSpell{1515}, // tame beast
                AddSpell{6991}, // Tier füttern
                AddSpell{883}, // Pet Call
                AddSpell{2641}, //Dismiss
            }},
        }},
        {12,
        {
            {SPELLFAMILY_ROGUE,
            {
                AddSpell{3127}, // parry
            }},
            {SPELLFAMILY_PALADIN,
            {
                AddSpell{7328}, // Redemption (R1)
            }},
        }},
        {14,
        {
            {SPELLFAMILY_HUNTER,
            {
                AddSpell{6197}, // eagle eye
            }},
        }},
        {16,
        {
            {SPELLFAMILY_ROGUE,
            {
                AddSpell{1804}, // Pick Lock
            }},
            {SPELLFAMILY_WARLOCK,
            {
                AddSpell{1455}, // Life Tap (R2)
            }},
        }},
        {20,
        {
            {SPELLFAMILY_WARRIOR,
            {
                AddSpell{674},   // dual wield
                AddSpell{12678}, // stance mastery
            }},
            {SPELLFAMILY_HUNTER,
            {
                AddSpell{674}, // dual wield
            }},
            {SPELLFAMILY_WARLOCK,
            {
              AddSpell{5784},   // [Felsteed]
            }},
            {SPELLFAMILY_PALADIN,
            {
              AddSpell{34769, TeamId::TEAM_HORDE}, // Schlachtross beschwören
              AddSpell{13819, TeamId::TEAM_ALLIANCE}, // Schlachtross beschwören
            }},
            {SPELLFAMILY_MAGE,
            {
              AddSpell{3567, TeamId::TEAM_HORDE}, // Teleport: Orgrimmar
              AddSpell{32272, TeamId::TEAM_HORDE}, // Teleport: Silvermoon
              AddSpell{3563, TeamId::TEAM_HORDE}, // Teleport: Undercity
              AddSpell{3561, TeamId::TEAM_ALLIANCE}, // Teleport: Stormwind
              AddSpell{3562, TeamId::TEAM_ALLIANCE}, // Teleport: Ironforge
              AddSpell{32271, TeamId::TEAM_ALLIANCE}, // Teleport: Exodar
            }},
        }},
        {24,
        {
            {SPELLFAMILY_HUNTER,
            {
                AddSpell{1462}, //  Beast Lore
                AddSpell{19885}, //  Track Hidden
            }},
            {SPELLFAMILY_ROGUE,
            {
                AddSpell{2836}, //  Detect Traps
            }},
            {SPELLFAMILY_WARLOCK,
            {
                AddSpell{5500}, //  Sense Demons
            }},
            {SPELLFAMILY_SHAMAN,
            {
                AddSpell{6196}, //  Far Sight
            }},
            {SPELLFAMILY_PALADIN,
            {
                AddSpell{10322}, // Redemption (R2)
            }},
        }},
        {26,
        {
            {SPELLFAMILY_WARLOCK,
            {
                AddSpell{1456}, // Life Tap (R3)
            }},
        }},
        {30,
        {
            {SPELLFAMILY_SHAMAN,
            {
                AddSpell{66842}, // Call of the Elements
            }},
            {SPELLFAMILY_MAGE,
            {
              AddSpell{3566, TeamId::TEAM_HORDE}, // Teleport: Thunder Bluf
              AddSpell{3565, TeamId::TEAM_ALLIANCE}, // Teleport: Darnassus
            }},
        }},
        {32,
        {
            {SPELLFAMILY_DRUID,
            {
                AddSpell{5225}, // Track Humanoids
            }},
        }},
        {35,
        {
            {SPELLFAMILY_MAGE,
            {
              AddSpell{49358, TeamId::TEAM_HORDE}, // Teleport: Stonard
              AddSpell{49361, TeamId::TEAM_HORDE}, // Portal: Stonard
              AddSpell{49359, TeamId::TEAM_ALLIANCE}, // Teleport: Theramore
              AddSpell{49360, TeamId::TEAM_ALLIANCE}, // Portal: Theramore
            }},
        }},
        {36,
        {
            {SPELLFAMILY_WARLOCK,
            {
                AddSpell{11687}, // Life Tap (R4)
            }},
            {SPELLFAMILY_PALADIN,
            {
                AddSpell{10324}, // Redemption (R3)
            }},
        }},
        {40,
        {
            {SPELLFAMILY_SHAMAN,
            {
                  AddSpell{66843}, // Call of the Ancestors
                  AddSpell{8737}, // Mail Rüstung
            }},
            {SPELLFAMILY_GENERIC,
            {
                  AddSpell{33388}, // Baby Mount
            }},
            {SPELLFAMILY_HUNTER,
            {
                  AddSpell{8737}, // Mail Rüstung
            }},
            {SPELLFAMILY_WARRIOR,
            {
                  AddSpell{750}, // PlatteMail Rüstung
            }},
            {SPELLFAMILY_PALADIN,
            {
                  AddSpell{34767, TeamId::TEAM_HORDE}, // Schlachtross beschwören
                  AddSpell{23214, TeamId::TEAM_ALLIANCE}, // Schlachtross beschwören
                  AddSpell{750}, // PlatteMail Rüstung
            }},
            {SPELLFAMILY_WARLOCK,
            {
                  AddSpell{23161}, // Dreadsteed
            }},
            {SPELLFAMILY_DRUID,
            {
                  AddSpell{20719}, // Feline Grace
                  AddSpell{62600}, // Savage Defense
            }},
            {SPELLFAMILY_MAGE,
            {
                  AddSpell{11417, TeamId::TEAM_HORDE}, // Portal: Orgrimmar
                  AddSpell{32267, TeamId::TEAM_HORDE}, // Portal: Silvermoon
                  AddSpell{11418, TeamId::TEAM_HORDE}, // Portal: Undercity
                  AddSpell{10059, TeamId::TEAM_ALLIANCE}, // Portal: Stormwind
                  AddSpell{11416, TeamId::TEAM_ALLIANCE}, // Portal: Ironforge
                  AddSpell{32266, TeamId::TEAM_ALLIANCE}, // Portal: Exodar
            }},
         },
        {46,
        {
           SPELLFAMILY_WARLOCK,
        {
               AddSpell{11688}, // Life Tap (R5)
        }},
        }},
        {48,
        {
        {SPELLFAMILY_PALADIN,
            {
                AddSpell{20772}, // Redemption (R4)
            }},
        }},
        {50,
        {
            {SPELLFAMILY_SHAMAN,
            {
                AddSpell{66844}, // Call of the Spirits
            }},
            {SPELLFAMILY_MAGE,
            {
                  AddSpell{11420, TeamId::TEAM_HORDE}, // Portal: Thunder Bluff
                  AddSpell{11419, TeamId::TEAM_ALLIANCE}, // Portal: Darnassus
            }},
        }},
        {56,
        {
            {SPELLFAMILY_WARLOCK,
            {
                AddSpell{11689}, // Life Tap (R6)
            }},
        }},
        {60,
        {
            {SPELLFAMILY_MAGE,
            {
                  AddSpell{35715, TeamId::TEAM_HORDE}, // Teleport: Shattrath
                  AddSpell{33690, TeamId::TEAM_ALLIANCE}, // Teleport: Shattrath
            }},
            {SPELLFAMILY_GENERIC,
            {
                  AddSpell{33391}, // Adult Mount
            }},
            {SPELLFAMILY_PALADIN,
            {
                  AddSpell{20773}, // Redemption (R5)
            }},
        }},
        {62,
        {
            {SPELLFAMILY_MAGE,
            {
                AddSpell{25306}, // Fireball (R12)
            }},
        }},
        {65,
        {
            {SPELLFAMILY_MAGE,
            {
                  AddSpell{35717, TeamId::TEAM_HORDE}, // Portal: Shattrath
                  AddSpell{33691, TeamId::TEAM_ALLIANCE}, // Portal: Shattrath
            }},
        }},
        {66,
        {
            {SPELLFAMILY_PALADIN,
            {
                AddSpell{53736, TeamId::TEAM_HORDE},    // Seal of Corruption
                AddSpell{31801, TeamId::TEAM_ALLIANCE}, // Seal of Vengeance
            }},
            {SPELLFAMILY_WARLOCK,
            {
                AddSpell{29858}, // Soulshatter
            }},
        }},
        {68,
        {
            {SPELLFAMILY_WARLOCK,
            {
                AddSpell{27222}, // Life Tap (R7)
            }},
        }},
        {70,
        {
            {SPELLFAMILY_SHAMAN,
            {
                AddSpell{2825, TeamId::TEAM_HORDE},     // Bloodlust
                AddSpell{32182, TeamId::TEAM_ALLIANCE}, // Heroism
            }},
            {SPELLFAMILY_GENERIC,
            {
                AddSpell{34090},     // Fly baby mounts
            }},
        }},
        {71,
        {
            {SPELLFAMILY_DRUID,
            {
                AddSpell{40120},     // Swift Flight Form                
            }},
        }},
        {72,
        {
            {SPELLFAMILY_PALADIN,
            {
                AddSpell{48949}, // Redemption (R6)
                
            }},
        }},
        {79,
        {
            {SPELLFAMILY_PALADIN,
            {
                AddSpell{48950}, // Redemption (R7)

            }},
        }},
        {80,
        {
            {SPELLFAMILY_WARLOCK,
            {
                AddSpell{47836}, // Seed of Corruption (rank 3)
                AddSpell{57946}, // Life Tap (R8)
            }},
            {SPELLFAMILY_GENERIC,
            {
                AddSpell{34091}, // Quick fly mounts
                AddSpell{54197}, // Flying in Northrend
            }},
        }},
    };
};

#define sChallengeModes ChallengeModes::instance()

#endif //CHALLENGEMODES_H
