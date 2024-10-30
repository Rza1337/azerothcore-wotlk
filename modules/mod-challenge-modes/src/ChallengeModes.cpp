/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ChallengeModes.h"
#include "SpellMgr.h"
#include "ChatCommand.h"
#include "Player.h"
#include "Chat.h"
#include "Config.h"
#include "DisableMgr.h"
#include "ScriptMgr.h"
#include "SpellInfo.h"

using namespace Acore::ChatCommands; // Brings ChatCommandTable into scope

ChallengeModes* ChallengeModes::instance()
{
    static ChallengeModes instance;
    return &instance;
}

bool ChallengeModes::challengeEnabledForPlayer(ChallengeModeSettings setting, Player* player) const
{
    if (!enabled() || !challengeEnabled(setting))
    {
        return false;
    }
    return player->GetPlayerSetting("mod-challenge-modes", setting).value;
}

bool ChallengeModes::challengeEnabled(ChallengeModeSettings setting) const
{
    switch (setting)
    {
        case SETTING_HARDCORE:
            return hardcoreEnable;
        case SETTING_SEMI_HARDCORE:
            return semiHardcoreEnable;
        case SETTING_SELF_CRAFTED:
            return selfCraftedEnable;
        case SETTING_ITEM_QUALITY_LEVEL:
            return itemQualityLevelEnable;
        case SETTING_SLOW_XP_GAIN:
            return slowXpGainEnable;
        case SETTING_VERY_SLOW_XP_GAIN:
            return verySlowXpGainEnable;
        case SETTING_TURTLE_MODE:
            return turtleModeEnable;
        case SETTING_QUEST_XP_ONLY:
            return questXpOnlyEnable;
        case SETTING_IRON_MAN:
            return ironManEnable;
        case SETTING_PACIFIST:
            return pacifistEnable;
        case SETTING_QUESTLESS:
            return questlessEnable;
        case SETTING_CASHLESS:
            return cashlessEnable;
        case HARDCORE_DEAD:
            break;
    }
    return false;
}

uint32 ChallengeModes::getDisableLevel(ChallengeModeSettings setting) const
{
    switch (setting)
    {
        case SETTING_HARDCORE:
            return hardcoreDisableLevel;
        case SETTING_SEMI_HARDCORE:
            return semiHardcoreDisableLevel;
        case SETTING_SELF_CRAFTED:
            return selfCraftedDisableLevel;
        case SETTING_ITEM_QUALITY_LEVEL:
            return itemQualityLevelDisableLevel;
        case SETTING_SLOW_XP_GAIN:
            return slowXpGainDisableLevel;
        case SETTING_VERY_SLOW_XP_GAIN:
            return verySlowXpGainDisableLevel;
        case SETTING_TURTLE_MODE:
            return turtleModeDisableLevel;
        case SETTING_QUEST_XP_ONLY:
            return questXpOnlyDisableLevel;
        case SETTING_IRON_MAN:
            return ironManDisableLevel;
        case SETTING_PACIFIST:
            return pacifistDisableLevel;
        case SETTING_QUESTLESS:
            return questlessDisableLevel;
        case SETTING_CASHLESS:
            return cashlessDisableLevel;
        case HARDCORE_DEAD:
            break;
    }
    return 0;
}

float ChallengeModes::getXpBonusForChallenge(ChallengeModeSettings setting) const
{
    switch (setting)
    {
        case SETTING_HARDCORE:
            return hardcoreXpBonus;
        case SETTING_SEMI_HARDCORE:
            return semiHardcoreXpBonus;
        case SETTING_SELF_CRAFTED:
            return selfCraftedXpBonus;
        case SETTING_ITEM_QUALITY_LEVEL:
            return itemQualityLevelXpBonus;
        case SETTING_SLOW_XP_GAIN:
            return slowXpGainBonus;
        case SETTING_VERY_SLOW_XP_GAIN:
            return verySlowXpGainBonus;
        case SETTING_TURTLE_MODE:
            return turtleModeXpGainBonus;
        case SETTING_QUEST_XP_ONLY:
            return questXpOnlyXpBonus;
        case SETTING_IRON_MAN:
            return ironManXpBonus;
        case SETTING_PACIFIST:
            return pacifistXpBonus;
        case SETTING_QUESTLESS:
            return questlessXpBonus;
        case SETTING_CASHLESS:
            return cashlessXpBonus;
        case HARDCORE_DEAD:
            break;
    }
    return 1;
}

const std::unordered_map<uint8, uint32> *ChallengeModes::getTitleMapForChallenge(ChallengeModeSettings setting) const
{
    switch (setting)
    {
        case SETTING_HARDCORE:
            return &hardcoreTitleRewards;
        case SETTING_SEMI_HARDCORE:
            return &semiHardcoreTitleRewards;
        case SETTING_SELF_CRAFTED:
            return &selfCraftedTitleRewards;
        case SETTING_ITEM_QUALITY_LEVEL:
            return &itemQualityLevelTitleRewards;
        case SETTING_SLOW_XP_GAIN:
            return &slowXpGainTitleRewards;
        case SETTING_VERY_SLOW_XP_GAIN:
            return &verySlowXpGainTitleRewards;
        case SETTING_TURTLE_MODE:
            return &turtleModeXpGainTitleRewards;
        case SETTING_QUEST_XP_ONLY:
            return &questXpOnlyTitleRewards;
        case SETTING_IRON_MAN:
            return &ironManTitleRewards;
        case SETTING_PACIFIST:
            return &pacifistTitleRewards;
        case SETTING_QUESTLESS:
            return &questlessTitleRewards;
        case SETTING_CASHLESS:
            return &cashlessTitleRewards;
        case HARDCORE_DEAD:
            break;
    }
    return {};
}

const std::unordered_map<uint8, uint32> *ChallengeModes::getTalentMapForChallenge(ChallengeModeSettings setting) const
{
    switch (setting)
    {
        case SETTING_HARDCORE:
            return &hardcoreTalentRewards;
        case SETTING_SEMI_HARDCORE:
            return &semiHardcoreTalentRewards;
        case SETTING_SELF_CRAFTED:
            return &selfCraftedTalentRewards;
        case SETTING_ITEM_QUALITY_LEVEL:
            return &itemQualityLevelTalentRewards;
        case SETTING_SLOW_XP_GAIN:
            return &slowXpGainTalentRewards;
        case SETTING_VERY_SLOW_XP_GAIN:
            return &verySlowXpGainTalentRewards;
        case SETTING_TURTLE_MODE:
            return &turtleModeXpGainTalentRewards;
        case SETTING_QUEST_XP_ONLY:
            return &questXpOnlyTalentRewards;
        case SETTING_IRON_MAN:
            return &ironManTalentRewards;
        case SETTING_PACIFIST:
            return &pacifistTalentRewards;
        case SETTING_QUESTLESS:
            return &questlessTalentRewards;
        case SETTING_CASHLESS:
            return &cashlessTalentRewards;
        case HARDCORE_DEAD:
            break;
    }
    return {};
}

const std::unordered_map<uint8, uint32> *ChallengeModes::getItemMapForChallenge(ChallengeModeSettings setting) const
{
    switch (setting)
    {
        case SETTING_HARDCORE:
            return &hardcoreItemRewards;
        case SETTING_SEMI_HARDCORE:
            return &semiHardcoreItemRewards;
        case SETTING_SELF_CRAFTED:
            return &selfCraftedItemRewards;
        case SETTING_ITEM_QUALITY_LEVEL:
            return &itemQualityLevelItemRewards;
        case SETTING_SLOW_XP_GAIN:
            return &slowXpGainItemRewards;
        case SETTING_VERY_SLOW_XP_GAIN:
            return &verySlowXpGainItemRewards;
        case SETTING_TURTLE_MODE:
            return &turtleModeXpGainItemRewards;
        case SETTING_QUEST_XP_ONLY:
            return &questXpOnlyItemRewards;
        case SETTING_IRON_MAN:
            return &ironManItemRewards;
        case SETTING_PACIFIST:
            return &pacifistItemRewards;
        case SETTING_QUESTLESS:
            return &questlessItemRewards;
        case SETTING_CASHLESS:
            return &cashlessItemRewards;
        case HARDCORE_DEAD:
            break;
    }
    return {};
}

uint32 ChallengeModes::getItemRewardAmount(ChallengeModeSettings setting) const
{
    switch (setting)
    {
        case SETTING_HARDCORE:
            return hardcoreItemRewardAmount;
        case SETTING_SEMI_HARDCORE:
            return semiHardcoreItemRewardAmount;
        case SETTING_SELF_CRAFTED:
            return selfCraftedItemRewardAmount;
        case SETTING_ITEM_QUALITY_LEVEL:
            return itemQualityLevelItemRewardAmount;
        case SETTING_SLOW_XP_GAIN:
            return slowXpGainItemRewardAmount;
        case SETTING_VERY_SLOW_XP_GAIN:
            return verySlowXpGainItemRewardAmount;
        case SETTING_TURTLE_MODE:
            return turtleModeXpGainItemRewardAmount;
        case SETTING_QUEST_XP_ONLY:
            return questXpOnlyItemRewardAmount;
        case SETTING_IRON_MAN:
            return ironManItemRewardAmount;
        case SETTING_PACIFIST:
            return pacifistItemRewardAmount;
        case SETTING_QUESTLESS:
            return questlessItemRewardAmount;
        case SETTING_CASHLESS:
            return cashlessItemRewardAmount;
        case HARDCORE_DEAD:
            break;
    }
    return 0;
}

const std::unordered_map<uint8, uint32> *ChallengeModes::getAchievementMapForChallenge(ChallengeModeSettings setting) const
{
    switch (setting)
    {
        case SETTING_HARDCORE:
            return &hardcoreAchievementReward;
        case SETTING_SEMI_HARDCORE:
            return &semiHardcoreAchievementReward;
        case SETTING_SELF_CRAFTED:
            return &selfCraftedAchievementReward;
        case SETTING_ITEM_QUALITY_LEVEL:
            return &itemQualityLevelAchievementReward;
        case SETTING_SLOW_XP_GAIN:
            return &slowXpGainAchievementReward;
        case SETTING_VERY_SLOW_XP_GAIN:
            return &verySlowXpGainAchievementReward;
        case SETTING_TURTLE_MODE:
            return &turtleModeXpGainAchievementReward;
        case SETTING_QUEST_XP_ONLY:
            return &questXpOnlyAchievementReward;
        case SETTING_IRON_MAN:
            return &ironManAchievementReward;
        case SETTING_PACIFIST:
            return &pacifistAchievementReward;
        case SETTING_QUESTLESS:
            return &questlessAchievementReward;
        case SETTING_CASHLESS:
            return &cashlessAchievementReward;
        case HARDCORE_DEAD:
            break;
    }
    return {};
}

class ChallengeModes_WorldScript : public WorldScript
{
public:
    ChallengeModes_WorldScript()
        : WorldScript("ChallengeModes_WorldScript")
    {}

    void OnBeforeConfigLoad(bool /*reload*/) override
    {
        LoadConfig();
    }

private:
    static void LoadStringToMap(std::unordered_map<uint8, uint32> &mapToLoad, const std::string &configString)
    {
        std::string delimitedValue;
        std::stringstream configIdStream;

        configIdStream.str(configString);
        // Process each config ID in the string, delimited by the comma - "," and then space " "
        while (std::getline(configIdStream, delimitedValue, ','))
        {
            std::string pairOne, pairTwo;
            std::stringstream configPairStream(delimitedValue);
            configPairStream>>pairOne>>pairTwo;
            auto configLevel = atoi(pairOne.c_str());
            auto rewardValue = atoi(pairTwo.c_str());
            mapToLoad[configLevel] = rewardValue;
        }
    }

    static void LoadConfig()
    {
        sChallengeModes->challengesEnabled = sConfigMgr->GetOption<bool>("ChallengeModes.Enable", false);
        if (sChallengeModes->enabled())
        {
            for (auto& [confName, rewardMap] : sChallengeModes->rewardConfigMap)
            {
                rewardMap->clear();
                LoadStringToMap(*rewardMap, sConfigMgr->GetOption<std::string>(confName, ""));
            }

            sChallengeModes->hardcoreEnable          = sConfigMgr->GetOption<bool>("Hardcore.Enable", true);
            sChallengeModes->semiHardcoreEnable      = sConfigMgr->GetOption<bool>("SemiHardcore.Enable", true);
            sChallengeModes->selfCraftedEnable       = sConfigMgr->GetOption<bool>("SelfCrafted.Enable", true);
            sChallengeModes->itemQualityLevelEnable  = sConfigMgr->GetOption<bool>("ItemQualityLevel.Enable", true);
            sChallengeModes->slowXpGainEnable        = sConfigMgr->GetOption<bool>("SlowXpGain.Enable", true);
            sChallengeModes->verySlowXpGainEnable    = sConfigMgr->GetOption<bool>("VerySlowXpGain.Enable", true);
            sChallengeModes->turtleModeEnable        = sConfigMgr->GetOption<bool>("TurtleMode.Enable", true);
            sChallengeModes->questXpOnlyEnable       = sConfigMgr->GetOption<bool>("QuestXpOnly.Enable", true);
            sChallengeModes->ironManEnable           = sConfigMgr->GetOption<bool>("IronMan.Enable", true);
            sChallengeModes->pacifistEnable          = sConfigMgr->GetOption<bool>("Pacifist.Enable", true);
            sChallengeModes->questlessEnable         = sConfigMgr->GetOption<bool>("Questless.Enable", true);
            sChallengeModes->cashlessEnable          = sConfigMgr->GetOption<bool>("Cashless.Enable", true);

            sChallengeModes->hardcoreDisableLevel          = sConfigMgr->GetOption<uint32>("Hardcore.DisableLevel", 0);
            sChallengeModes->semiHardcoreDisableLevel      = sConfigMgr->GetOption<uint32>("SemiHardcore.DisableLevel", 0);
            sChallengeModes->selfCraftedDisableLevel       = sConfigMgr->GetOption<uint32>("SelfCrafted.DisableLevel", 0);
            sChallengeModes->itemQualityLevelDisableLevel  = sConfigMgr->GetOption<uint32>("ItemQualityLevel.DisableLevel", 0);
            sChallengeModes->slowXpGainDisableLevel        = sConfigMgr->GetOption<uint32>("SlowXpGain.DisableLevel", 0);
            sChallengeModes->verySlowXpGainDisableLevel    = sConfigMgr->GetOption<uint32>("VerySlowXpGain.DisableLevel", 0);
            sChallengeModes->turtleModeDisableLevel        = sConfigMgr->GetOption<uint32>("TurtleModeXpGain.DisableLevel", 0);
            sChallengeModes->questXpOnlyDisableLevel       = sConfigMgr->GetOption<uint32>("QuestXpOnly.DisableLevel", 0);
            sChallengeModes->ironManDisableLevel           = sConfigMgr->GetOption<uint32>("IronMan.DisableLevel", 0);
            sChallengeModes->pacifistDisableLevel          = sConfigMgr->GetOption<uint32>("Pacifist.DisableLevel", 0);
            sChallengeModes->questlessDisableLevel         = sConfigMgr->GetOption<uint32>("Questless.DisableLevel", 0);
            sChallengeModes->cashlessDisableLevel          = sConfigMgr->GetOption<uint32>("Cashless.DisableLevel", 0);

            sChallengeModes->hardcoreXpBonus         = sConfigMgr->GetOption<float>("Hardcore.XPMultiplier", 1.0f);
            sChallengeModes->semiHardcoreXpBonus     = sConfigMgr->GetOption<float>("SemiHardcore.XPMultiplier", 1.0f);
            sChallengeModes->selfCraftedXpBonus      = sConfigMgr->GetOption<float>("SelfCrafted.XPMultiplier", 1.0f);
            sChallengeModes->itemQualityLevelXpBonus = sConfigMgr->GetOption<float>("ItemQualityLevel.XPMultiplier", 1.0f);
            sChallengeModes->questXpOnlyXpBonus      = sConfigMgr->GetOption<float>("QuestXpOnly.XPMultiplier", 1.0f);
            sChallengeModes->slowXpGainBonus         = sConfigMgr->GetOption<float>("SlowXpGain.XPMultiplier", 0.50f);
            sChallengeModes->verySlowXpGainBonus     = sConfigMgr->GetOption<float>("VerySlowXpGain.XPMultiplier", 0.25f);
            sChallengeModes->turtleModeXpGainBonus   = sConfigMgr->GetOption<float>("TurtleModeXpGain.XPMultiplier", 0.10f);
            sChallengeModes->ironManXpBonus          = sConfigMgr->GetOption<float>("IronMan.XPMultiplier", 1.0f);
            sChallengeModes->pacifistXpBonus         = sConfigMgr->GetOption<float>("Pacifist.XPMultiplier", 1.0f);
            sChallengeModes->questlessXpBonus        = sConfigMgr->GetOption<float>("Questless.XPMultiplier", 1.0f);
            sChallengeModes->cashlessXpBonus         = sConfigMgr->GetOption<float>("Cashless.XPMultiplier", 1.0f);

            sChallengeModes->hardcoreItemRewardAmount         = sConfigMgr->GetOption<uint32>("Hardcore.ItemRewardAmount", 1);
            sChallengeModes->semiHardcoreItemRewardAmount     = sConfigMgr->GetOption<uint32>("SemiHardcore.ItemRewardAmount", 1);
            sChallengeModes->selfCraftedItemRewardAmount      = sConfigMgr->GetOption<uint32>("SelfCrafted.ItemRewardAmount", 1);
            sChallengeModes->itemQualityLevelItemRewardAmount = sConfigMgr->GetOption<uint32>("ItemQualityLevel.ItemRewardAmount", 1);
            sChallengeModes->slowXpGainItemRewardAmount       = sConfigMgr->GetOption<uint32>("SlowXpGain.ItemRewardAmount", 1);
            sChallengeModes->verySlowXpGainItemRewardAmount   = sConfigMgr->GetOption<uint32>("VerySlowXpGain.ItemRewardAmount", 1);
            sChallengeModes->turtleModeXpGainItemRewardAmount = sConfigMgr->GetOption<uint32>("TurtleModeXpGain.ItemRewardAmount", 1);
            sChallengeModes->questXpOnlyItemRewardAmount      = sConfigMgr->GetOption<uint32>("QuestXpOnly.ItemRewardAmount", 1);
            sChallengeModes->ironManItemRewardAmount          = sConfigMgr->GetOption<uint32>("IronMan.ItemRewardAmount", 1);
            sChallengeModes->pacifistItemRewardAmount         = sConfigMgr->GetOption<uint32>("Pacifist.ItemRewardAmount", 1);
            sChallengeModes->questlessItemRewardAmount        = sConfigMgr->GetOption<uint32>("Questless.ItemRewardAmount", 1);
            sChallengeModes->cashlessItemRewardAmount         = sConfigMgr->GetOption<uint32>("Cashless.ItemRewardAmount", 1);

            LoadStringToMap(sChallengeModes->hardcoreAchievementReward, sConfigMgr->GetOption<std::string>("Hardcore.AchievementReward", ""));
            LoadStringToMap(sChallengeModes->semiHardcoreAchievementReward, sConfigMgr->GetOption<std::string>("SemiHardcore.AchievementReward", ""));
            LoadStringToMap(sChallengeModes->selfCraftedAchievementReward, sConfigMgr->GetOption<std::string>("SelfCrafted.AchievementReward", ""));
            LoadStringToMap(sChallengeModes->itemQualityLevelAchievementReward, sConfigMgr->GetOption<std::string>("ItemQualityLevel.AchievementReward", ""));
            LoadStringToMap(sChallengeModes->slowXpGainAchievementReward, sConfigMgr->GetOption<std::string>("SlowXpGain.AchievementReward", ""));
            LoadStringToMap(sChallengeModes->verySlowXpGainAchievementReward, sConfigMgr->GetOption<std::string>("VerySlowXpGain.AchievementReward", ""));
            LoadStringToMap(sChallengeModes->turtleModeXpGainAchievementReward, sConfigMgr->GetOption<std::string>("TurtleModeXpGain.AchievementReward", ""));
            LoadStringToMap(sChallengeModes->questXpOnlyAchievementReward, sConfigMgr->GetOption<std::string>("QuestXpOnly.AchievementReward", ""));
            LoadStringToMap(sChallengeModes->ironManAchievementReward, sConfigMgr->GetOption<std::string>("IronMan.AchievementReward", ""));
            LoadStringToMap(sChallengeModes->pacifistAchievementReward, sConfigMgr->GetOption<std::string>("Pacifist.AchievementReward", ""));
            LoadStringToMap(sChallengeModes->questlessAchievementReward, sConfigMgr->GetOption<std::string>("Questless.AchievementReward", ""));
            LoadStringToMap(sChallengeModes->cashlessAchievementReward, sConfigMgr->GetOption<std::string>("Cashless.AchievementReward", ""));

        }
    }
};

class ChallengeMode : public PlayerScript
{
public:
    explicit ChallengeMode(const char *scriptName,
                           ChallengeModeSettings settingName)
            : PlayerScript(scriptName), settingName(settingName)
    { }

    static bool mapContainsKey(const std::unordered_map<uint8, uint32>* mapToCheck, uint8 key)
    {
        return (mapToCheck->find(key) != mapToCheck->end());
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* /*victim*/, uint8 /*xpSource*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(settingName, player))
        {
            return;
        }
        amount *= sChallengeModes->getXpBonusForChallenge(settingName);
    }

void OnLevelChanged(Player* player, uint8 /*oldlevel*/) override
{
    if (!sChallengeModes->challengeEnabledForPlayer(settingName, player))
    {
        return;
    }

    const std::unordered_map<uint8, uint32>* titleRewardMap = sChallengeModes->getTitleMapForChallenge(settingName);
    const std::unordered_map<uint8, uint32>* talentRewardMap = sChallengeModes->getTalentMapForChallenge(settingName);
    const std::unordered_map<uint8, uint32>* itemRewardMap = sChallengeModes->getItemMapForChallenge(settingName);
    const std::unordered_map<uint8, uint32>* achievementRewardMap = sChallengeModes->getAchievementMapForChallenge(settingName);
    uint8 level = player->GetLevel();

    if (mapContainsKey(titleRewardMap, level))
    {
        CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(titleRewardMap->at(level));
        if (!titleInfo)
        {
            LOG_ERROR("mod-challenge-modes", "Invalid title ID {}!", titleRewardMap->at(level));
            return;
        }
        ChatHandler handler(player->GetSession());
        std::string tNameLink = handler.GetNameLink(player);
        std::string titleNameStr = Acore::StringFormat(player->getGender() == GENDER_MALE ? titleInfo->nameMale[handler.GetSessionDbcLocale()] : titleInfo->nameFemale[handler.GetSessionDbcLocale()], player->GetName());
        player->SetTitle(titleInfo);
    }

    if (mapContainsKey(talentRewardMap, level))
    {
        player->RewardExtraBonusTalentPoints(talentRewardMap->at(level));
    }

    if (mapContainsKey(achievementRewardMap, level))
    {
        AchievementEntry const* achievementInfo = sAchievementStore.LookupEntry(achievementRewardMap->at(level));
        if (!achievementInfo)
        {
            LOG_ERROR("mod-challenge-modes", "Invalid Achievement ID {}!", achievementRewardMap->at(level));
            return;
        }

        ChatHandler handler(player->GetSession());
        std::string tNameLink = handler.GetNameLink(player);
        player->CompletedAchievement(achievementInfo);
    }

    if (mapContainsKey(itemRewardMap, level))
    {
        uint32 itemEntry = itemRewardMap->at(level);
        uint32 itemAmount = sChallengeModes->getItemRewardAmount(settingName); // Fetch item amount from config
        player->SendItemRetrievalMail({ { itemEntry, itemAmount } });
    }

    if (sChallengeModes->getDisableLevel(settingName) && sChallengeModes->getDisableLevel(settingName) <= level)
    {
        player->UpdatePlayerSetting("mod-challenge-modes", settingName, 0);
    }
}

private:
    ChallengeModeSettings settingName;
};

class ChallengeMode_Hardcore : public ChallengeMode
{
public:
    ChallengeMode_Hardcore() : ChallengeMode("ChallengeMode_Hardcore", SETTING_HARDCORE) {}

    void OnLogin(Player* player) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_HARDCORE, player) || !sChallengeModes->challengeEnabledForPlayer(HARDCORE_DEAD, player))
        {
            return;
        }
        player->KillPlayer();
        player->GetSession()->KickPlayer("Hardcore character died");
    }

    void OnPlayerReleasedGhost(Player* player) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_HARDCORE, player))
        {
            return;
        }
        player->UpdatePlayerSetting("mod-challenge-modes", HARDCORE_DEAD, 1);
        player->GetSession()->KickPlayer("Hardcore character died");
    }

    void OnPVPKill(Player* /*killer*/, Player* killed) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_HARDCORE, killed))
        {
            return;
        }
        killed->UpdatePlayerSetting("mod-challenge-modes", HARDCORE_DEAD, 1);
    }

    void OnPlayerKilledByCreature(Creature* /*killer*/, Player* killed) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_HARDCORE, killed))
        {
            return;
        }
        killed->UpdatePlayerSetting("mod-challenge-modes", HARDCORE_DEAD, 1);
    }

    void OnPlayerResurrect(Player* player, float /*restore_percent*/, bool /*applySickness*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_HARDCORE, player))
        {
            return;
        }
        // A better implementation is to not allow the resurrect but this will need a new hook added first
        player->UpdatePlayerSetting("mod-challenge-modes", HARDCORE_DEAD, 1);
        player->KillPlayer();
        player->GetSession()->KickPlayer("Hardcore character died");
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        ChallengeMode::OnGiveXP(player, amount, victim, xpSource);
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
};

class ChallengeMode_SemiHardcore : public ChallengeMode
{
public:
    ChallengeMode_SemiHardcore() : ChallengeMode("ChallengeMode_SemiHardcore", SETTING_SEMI_HARDCORE) {}

    void OnPlayerKilledByCreature(Creature* /*killer*/, Player* player) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_SEMI_HARDCORE, player))
        {
            return;
        }
        for (uint8 i = 0; i < EQUIPMENT_SLOT_END; ++i)
        {
            if (Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            {
                if (pItem->GetTemplate() && !pItem->IsEquipped())
                    continue;
                uint8 slot = pItem->GetSlot();
                ChatHandler(player->GetSession()).PSendSysMessage("|cffDA70D6You have lost your |cffffffff|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r", pItem->GetEntry(), pItem->GetTemplate()->Name1.c_str());
                player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);
            }
        }
        player->SetMoney(0);
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        ChallengeMode::OnGiveXP(player, amount, victim, xpSource);
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
};

class ChallengeMode_SelfCrafted : public ChallengeMode
{
public:
    ChallengeMode_SelfCrafted() : ChallengeMode("ChallengeMode_SelfCrafted", SETTING_SELF_CRAFTED) {}

    bool CanEquipItem(Player* player, uint8 /*slot*/, uint16& /*dest*/, Item* pItem, bool /*swap*/, bool /*not_loading*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_SELF_CRAFTED, player))
        {
            return true;
        }
        if (!pItem->GetTemplate()->HasSignature())
        {
            return false;
        }
        return pItem->GetGuidValue(ITEM_FIELD_CREATOR) == player->GetGUID();
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        ChallengeMode::OnGiveXP(player, amount, victim, xpSource);
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
};

class ChallengeMode_ItemQualityLevel : public ChallengeMode
{
public:
    ChallengeMode_ItemQualityLevel() : ChallengeMode("ChallengeMode_ItemQualityLevel", SETTING_ITEM_QUALITY_LEVEL) {}

    bool CanEquipItem(Player* player, uint8 /*slot*/, uint16& /*dest*/, Item* pItem, bool /*swap*/, bool /*not_loading*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_ITEM_QUALITY_LEVEL, player))
        {
            return true;
        }
        return pItem->GetTemplate()->Quality <= ITEM_QUALITY_NORMAL;
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        ChallengeMode::OnGiveXP(player, amount, victim, xpSource);
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
};

class ChallengeMode_SlowXpGain : public ChallengeMode
{
public:
    ChallengeMode_SlowXpGain() : ChallengeMode("ChallengeMode_SlowXpGain", SETTING_SLOW_XP_GAIN) {}

    void OnGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        ChallengeMode::OnGiveXP(player, amount, victim, xpSource);
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
};

class ChallengeMode_VerySlowXpGain : public ChallengeMode
{
public:
    ChallengeMode_VerySlowXpGain() : ChallengeMode("ChallengeMode_VerySlowXpGain", SETTING_VERY_SLOW_XP_GAIN) {}

    void OnGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        ChallengeMode::OnGiveXP(player, amount, victim, xpSource);
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
};

class ChallengeMode_TurtleMode : public ChallengeMode
{
public:
    ChallengeMode_TurtleMode() : ChallengeMode("ChallengeMode_TurtleMode", SETTING_TURTLE_MODE) {}

    void OnGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        ChallengeMode::OnGiveXP(player, amount, victim, xpSource);
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
};

class ChallengeMode_QuestXpOnly : public ChallengeMode
{
public:
    ChallengeMode_QuestXpOnly() : ChallengeMode("ChallengeMode_QuestXpOnly", SETTING_QUEST_XP_ONLY) {}

    void OnGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_QUEST_XP_ONLY, player))
        {
            return;
        }
        if (victim)
        {
            // Still award XP to pets - they won't be able to pass the player's level
            Pet* pet = player->GetPet();
            if (pet && xpSource == XPSOURCE_KILL) {
                 pet->GivePetXP(player->GetGroup() ? amount / 2 : amount);
            }
            amount = 0;
        }
        else
        {
            if ( xpSource == XPSOURCE_BATTLEGROUND ) {
                amount = 0;
                return;
            }
            ChallengeMode::OnGiveXP(player, amount, victim, xpSource);
        }
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
};

class ChallengeMode_IronMan : public ChallengeMode
{
public:
    ChallengeMode_IronMan() : ChallengeMode("ChallengeMode_IronMan", SETTING_IRON_MAN) {}

    void OnPlayerResurrect(Player* player, float /*restore_percent*/, bool /*applySickness*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return;
        }
        // A better implementation is to not allow the resurrect but this will need a new hook added first
        player->KillPlayer();
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        ChallengeMode::OnGiveXP(player, amount, victim, xpSource);
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return;
        }
        player->SetFreeTalentPoints(0); // Remove all talent points
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }

    void OnTalentsReset(Player* player, bool /*noCost*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return;
        }
        player->SetFreeTalentPoints(0); // Remove all talent points
    }

    bool CanEquipItem(Player* player, uint8 /*slot*/, uint16& /*dest*/, Item* pItem, bool /*swap*/, bool /*not_loading*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return true;
        }
        return pItem->GetTemplate()->Quality <= ITEM_QUALITY_NORMAL;
    }

    bool CanApplyEnchantment(Player* player, Item* /*item*/, EnchantmentSlot /*slot*/, bool /*apply*/, bool /*apply_dur*/, bool /*ignore_condition*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return true;
        }
        // Are there any exceptions in WotLK? If so need to be added here
        return false;
    }

    void OnLearnSpell(Player* player, uint32 spellID) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return;
        }
        // These professions are class skills so they are always acceptable
        switch (spellID)
        {
            case RUNEFORGING:
            case POISONS:
            case BEAST_TRAINING:
                return;
            default:
                break;
        }
        // Do not allow learning any trade skills
        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellID);
        if (!spellInfo)
            return;
        bool shouldForget = false;
        for (uint8 i = 0; i < 3; i++)
        {
            if (spellInfo->Effects[i].Effect == SPELL_EFFECT_TRADE_SKILL)
            {
                shouldForget = true;
            }
        }
        if (shouldForget)
        {
            player->removeSpell(spellID, SPEC_MASK_ALL, false);
        }
    }

    bool CanUseItem(Player* player, ItemTemplate const* proto, InventoryResult& /*result*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return true;
        }
        // Do not allow using elixir, potion, or flask
        if (proto->Class == ITEM_CLASS_CONSUMABLE &&
                (proto->SubClass == ITEM_SUBCLASS_POTION ||
                proto->SubClass == ITEM_SUBCLASS_ELIXIR ||
                proto->SubClass == ITEM_SUBCLASS_FLASK))
        {
            return false;
        }
        // Do not allow food that gives food buffs
        if (proto->Class == ITEM_CLASS_CONSUMABLE && proto->SubClass == ITEM_SUBCLASS_FOOD)
        {
            for (const auto & Spell : proto->Spells)
            {
                SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(Spell.SpellId);
                if (!spellInfo)
                    continue;

                for (uint8 i = 0; i < 3; i++)
                {
                    if (spellInfo->Effects[i].ApplyAuraName == SPELL_AURA_PERIODIC_TRIGGER_SPELL)
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool CanGroupInvite(Player* player, std::string& /*membername*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return true;
        }
        return false;
    }

    bool CanGroupAccept(Player* player, Group* /*group*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return true;
        }
        return false;
    }

};

class ChallengeMode_Pacifist : public UnitScript
{
public:
    ChallengeMode_Pacifist() : UnitScript("ChallengeMode_Pacifist") {}

    // Nullify damage dealt by pacifist players and pets
    void OnDamage(Unit* attacker, Unit* /*victim*/, uint32& damage) override
    {
        Player* player = nullptr;

        // Check if the attacker is a player or their pet
        if (attacker->GetTypeId() == TYPEID_PLAYER)
        {
            player = attacker->ToPlayer();
        }
        else if (attacker->GetTypeId() == TYPEID_UNIT && attacker->ToCreature()->IsPet())
        {
            player = attacker->GetOwner() ? attacker->GetOwner()->ToPlayer() : nullptr;
        }

        // Nullify damage if pacifist mode is enabled for the player or pet owner
        if (player && sChallengeModes->challengeEnabledForPlayer(SETTING_PACIFIST, player))
        {
            damage = 0;
            ChatHandler(player->GetSession()).PSendSysMessage("Pacifists cannot deal damage.");
        }
    }
};

class ChallengeMode_Questless : public ChallengeMode
{
public:
    ChallengeMode_Questless() : ChallengeMode("ChallengeMode_Questless", SETTING_QUESTLESS){}

    void OnGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        (void)victim;
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_QUESTLESS, player))
        {
            return;
        }
            if ( xpSource == XPSOURCE_QUEST ) {
                amount = 0;
            }
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }

};

class ChallengeMode_Cashless : public ChallengeMode
{
public:
    ChallengeMode_Cashless() : ChallengeMode("ChallengeMode_Cashless", SETTING_CASHLESS) {}

    void OnMoneyChanged(Player* player, int32& amount) override
    {
        // Check if cashless mode is enabled
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_CASHLESS, player)) {
            if (amount > 0)
            {
                amount = 0;
            }
        }
    }

    void OnLevelChanged(Player* player, uint8 oldLevel) override
    {

        if( oldLevel < player->GetLevel() ) {
            sChallengeModes->LearnSpellsForNewLevel(player, oldLevel);
        }

        ChallengeMode::OnLevelChanged(player, oldLevel);
    }

};

class ChallengeMode_Commands : public CommandScript
{
public:
    ChallengeMode_Commands() : CommandScript("ChallengeMode_Commands") {}

ChatCommandTable GetCommands() const override
{
    static ChatCommandTable commandTable =
    {
        ChatCommandBuilder("challenge", ChatCommandTable
            {
                ChatCommandBuilder("enable", HandleEnableChallengeCommand, SEC_ADMINISTRATOR, Acore::ChatCommands::Console::No),
                ChatCommandBuilder("disable", HandleDisableChallengeCommand, SEC_ADMINISTRATOR, Acore::ChatCommands::Console::No),
                ChatCommandBuilder("active", HandleViewActiveChallengesCommand, SEC_ADMINISTRATOR, Acore::ChatCommands::Console::No),
                ChatCommandBuilder("talent", HandleTalentPointsCommand, SEC_ADMINISTRATOR, Acore::ChatCommands::Console::No)
            }
        )
    };
    return commandTable;
}


    static bool HandleChallengeCommand(ChatHandler* handler, const char* /*args*/)
    {
        handler->SendSysMessage("Challenge command:");
        return true;
    }

    // Enable Challenge Command
    static bool HandleEnableChallengeCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (!*args)
            return false;

        int setting = atoi(args);
        if (setting < 0 || setting >= HARDCORE_DEAD)
        {
            handler->SendSysMessage("Invalid challenge setting ID.");
            return false;
        }

        player->UpdatePlayerSetting("mod-challenge-modes", setting, 1);
        handler->PSendSysMessage("Challenge %d enabled for %s.", setting, player->GetName().c_str());
        return true;
    }

    // Disable Challenge Command
    static bool HandleDisableChallengeCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (!*args)
            return false;

        int setting = atoi(args);
        if (setting < 0 || setting >= HARDCORE_DEAD)
        {
            handler->SendSysMessage("Invalid challenge setting ID.");
            return false;
        }

        player->UpdatePlayerSetting("mod-challenge-modes", setting, 0);
        handler->PSendSysMessage("Challenge %d disabled for %s.", setting, player->GetName().c_str());
        return true;
    }

    // View Active Challenges Command
    static bool HandleViewActiveChallengesCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        std::string activeChallenges = "Active Challenges for " + player->GetName() + ":\n";

        for (int i = 0; i <= HARDCORE_DEAD; ++i)
        {
            if (sChallengeModes->challengeEnabledForPlayer(static_cast<ChallengeModeSettings>(i), player))
            {
                activeChallenges += " - Challenge " + std::to_string(i) + " is active.\n";
            }
        }

        handler->SendSysMessage(activeChallenges.c_str());
        return true;
    }

    // Add/Remove Talent Points Command
    static bool HandleTalentPointsCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (!*args)
            return false;

        int points = atoi(args);
        if (points == 0)
        {
            handler->SendSysMessage("Invalid number of points. Use a positive or negative integer.");
            return false;
        }

        int currentPoints = player->GetFreeTalentPoints();
        int newPoints = currentPoints + points;
        if (newPoints < 0)
        {
            handler->SendSysMessage("Error: Cannot have negative talent points.");
            return false;
        }

        player->SetFreeTalentPoints(newPoints);
        handler->PSendSysMessage("Talent points adjusted by %d. New total: %d.", points, newPoints);
        return true;
    }
};

class gobject_challenge_modes : public GameObjectScript
{
private:
    static bool playerSettingEnabled(Player* player, uint8 settingIndex)
    {
        return player->GetPlayerSetting("mod-challenge-modes", settingIndex).value;
    }

public:
    gobject_challenge_modes() : GameObjectScript("gobject_challenge_modes") { }

    struct gobject_challenge_modesAI: GameObjectAI
    {
        explicit gobject_challenge_modesAI(GameObject* object) : GameObjectAI(object) { };

        bool CanBeSeen(Player const* player) override
        {
            if ((player->GetLevel() > 1 && player->getClass() != CLASS_DEATH_KNIGHT) || (player->GetLevel() > 55))
            {
                return false;
            }
            return sChallengeModes->enabled();
        }
    };

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (sChallengeModes->challengeEnabled(SETTING_IRON_MAN) && !playerSettingEnabled(player, SETTING_IRON_MAN) && !playerSettingEnabled(player, SETTING_SELF_CRAFTED)  && !playerSettingEnabled(player, SETTING_HARDCORE)  && !playerSettingEnabled(player, SETTING_SEMI_HARDCORE)  && !playerSettingEnabled(player, SETTING_ITEM_QUALITY_LEVEL))
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Enable Iron Man Mode", 0, SETTING_IRON_MAN);
        }
        if (sChallengeModes->challengeEnabled(SETTING_HARDCORE) && !playerSettingEnabled(player, SETTING_HARDCORE) && !playerSettingEnabled(player, SETTING_SEMI_HARDCORE)  && !playerSettingEnabled(player, SETTING_IRON_MAN))
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Enable Hardcore Mode", 0, SETTING_HARDCORE);
        }
        if (sChallengeModes->challengeEnabled(SETTING_SEMI_HARDCORE) && !playerSettingEnabled(player, SETTING_HARDCORE) && !playerSettingEnabled(player, SETTING_SEMI_HARDCORE)  && !playerSettingEnabled(player, SETTING_IRON_MAN))
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Enable Semi-Hardcore Mode", 0, SETTING_SEMI_HARDCORE);
        }
        if (sChallengeModes->challengeEnabled(SETTING_SELF_CRAFTED) && !playerSettingEnabled(player, SETTING_SELF_CRAFTED) && !playerSettingEnabled(player, SETTING_IRON_MAN))
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Enable Self-Crafted Mode", 0, SETTING_SELF_CRAFTED);
        }
        if (sChallengeModes->challengeEnabled(SETTING_ITEM_QUALITY_LEVEL) && !playerSettingEnabled(player, SETTING_ITEM_QUALITY_LEVEL) && !playerSettingEnabled(player, SETTING_IRON_MAN))
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Enable Low Quality Item Mode", 0, SETTING_ITEM_QUALITY_LEVEL);
        }
        if (sChallengeModes->challengeEnabled(SETTING_SLOW_XP_GAIN) && !playerSettingEnabled(player, SETTING_SLOW_XP_GAIN) && !playerSettingEnabled(player, SETTING_VERY_SLOW_XP_GAIN) && !playerSettingEnabled(player, SETTING_TURTLE_MODE))
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Enable Slow XP Mode", 0, SETTING_SLOW_XP_GAIN);
        }
        if (sChallengeModes->challengeEnabled(SETTING_VERY_SLOW_XP_GAIN) && !playerSettingEnabled(player, SETTING_SLOW_XP_GAIN) && !playerSettingEnabled(player, SETTING_VERY_SLOW_XP_GAIN) && !playerSettingEnabled(player, SETTING_TURTLE_MODE))
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Enable Very Slow XP Mode", 0, SETTING_VERY_SLOW_XP_GAIN);
        }
        if (sChallengeModes->challengeEnabled(SETTING_TURTLE_MODE) && !playerSettingEnabled(player, SETTING_SLOW_XP_GAIN) && !playerSettingEnabled(player, SETTING_VERY_SLOW_XP_GAIN) && !playerSettingEnabled(player, SETTING_TURTLE_MODE))
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Enable Very Very Very Slow XP Mode", 0, SETTING_TURTLE_MODE);
        }
        if (sChallengeModes->challengeEnabled(SETTING_CASHLESS) && !playerSettingEnabled(player, SETTING_CASHLESS))
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Enable Cashless Mode", 0, SETTING_CASHLESS);
        }
        if (sChallengeModes->challengeEnabled(SETTING_QUESTLESS) && !playerSettingEnabled(player, SETTING_QUESTLESS) && !playerSettingEnabled(player, SETTING_QUEST_XP_ONLY))
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Enable Questless Mode", 0, SETTING_QUESTLESS);
        }
        if (sChallengeModes->challengeEnabled(SETTING_QUEST_XP_ONLY) && !playerSettingEnabled(player, SETTING_QUEST_XP_ONLY) && !playerSettingEnabled(player, SETTING_QUESTLESS))
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Enable Quest XP Only Mode", 0, SETTING_QUEST_XP_ONLY);
        }
        if (sChallengeModes->challengeEnabled(SETTING_PACIFIST) && !playerSettingEnabled(player, SETTING_PACIFIST))
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Enable Pacifist Mode", 0, SETTING_PACIFIST);
        }
        SendGossipMenuFor(player, 12669, go->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, GameObject* /*go*/, uint32 /*sender*/, uint32 action) override
    {
        player->UpdatePlayerSetting("mod-challenge-modes", action, 1);
        ChatHandler(player->GetSession()).PSendSysMessage("Challenge enabled.");
        CloseGossipMenuFor(player);
        return true;
    }

    GameObjectAI* GetAI(GameObject* object) const override
    {
        return new gobject_challenge_modesAI(object);
    }

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
         }},
        {46,
        {
           {SPELLFAMILY_WARLOCK,
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

    bool IsIgnoredSpell(uint32 spellID)
    {
        return m_ignoreSpells.find(spellID) != m_ignoreSpells.end();
    }

    void LearnSpellsForNewLevel(Player* player, uint8 fromLevel)
    {
        uint8 upToLevel = player->GetLevel();
        uint32 family = GetSpellFamily(player);

        for (int level = fromLevel; level <= upToLevel; level++)
        {
            ApplyAdditionalSpells(level, family, player);

            for (uint32 i = 0; i < sSpellMgr->GetSpellInfoStoreSize(); ++i)
            {
                SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(i);

                if (!spellInfo)
                    continue;

                if (spellInfo->SpellFamilyName != family)
                    continue;

                if ((spellInfo->AttributesEx7 & SPELL_ATTR7_ALLIANCE_SPECIFIC_SPELL && player->GetTeamId() != TEAM_ALLIANCE) || (spellInfo->AttributesEx7 & SPELL_ATTR7_HORDE_SPECIFIC_SPELL && player->GetTeamId() != TEAM_HORDE))
                    continue;

                if (spellInfo->PowerType == POWER_FOCUS)
                    continue;

                if (IsIgnoredSpell(spellInfo->Id))
                    continue;

                if (DisableMgr::IsDisabledFor(DISABLE_TYPE_SPELL, spellInfo->Id, player))
                    continue;

                if (spellInfo->BaseLevel != uint32(level) && sSpellMgr->IsSpellValid(spellInfo))
                    continue;

                bool valid = false;

                SkillLineAbilityMapBounds bounds = sSpellMgr->GetSkillLineAbilityMapBounds(spellInfo->Id);

                for (auto itr = bounds.first; itr != bounds.second; ++itr)
                {
                    if (itr->second->Spell == spellInfo->Id && itr->second->RaceMask == 0 && itr->second->AcquireMethod == 0)
                    {
                        valid = true;
                        SpellInfo const* prevSpell = spellInfo->GetPrevRankSpell();

                        if (prevSpell && !player->HasSpell(prevSpell->Id))
                        {
                            valid = false;
                            break;
                        }

                        if (GetTalentSpellPos(itr->second->Spell))
                            if (!prevSpell || !player->HasSpell(prevSpell->Id) || spellInfo->GetRank() == 1)
                                valid = false;

                        break;
                    }
                }

                if (valid)
                    player->learnSpell(spellInfo->Id);
            }
        }
    }

    void ApplyAdditionalSpells(uint8 level, uint32 playerSpellFamily, Player* player)
    {
        auto spells = m_additionalSpells.find(level);
        if (spells != m_additionalSpells.end())
        {
            SpellFamilyToExtraSpells spellsMap = spells->second;

            auto spellsForPlayersFamily = spellsMap.find(playerSpellFamily);
            if (spellsForPlayersFamily != spellsMap.end())
            {
                std::vector<AddSpell> additionalSpellsToTeach = spellsForPlayersFamily->second;
                for (auto const& spell : additionalSpellsToTeach)
                {
                    if (!(player->HasSpell(spell.spellId)) && (spell.faction == TeamId::TEAM_NEUTRAL || spell.faction == player->GetTeamId()))
                    {
                        player->learnSpell(spell.spellId);
                    }
                }
            }
        }
    }

    uint32 GetSpellFamily(const Player* p)
    {
        switch (p->getClass())
        {
        case CLASS_ROGUE:
            return SPELLFAMILY_ROGUE;
        case CLASS_DEATH_KNIGHT:
            return SPELLFAMILY_DEATHKNIGHT;
        case CLASS_WARRIOR:
            return SPELLFAMILY_WARRIOR;
        case CLASS_PRIEST:
            return SPELLFAMILY_PRIEST;
        case CLASS_MAGE:
            return SPELLFAMILY_MAGE;
        case CLASS_PALADIN:
            return SPELLFAMILY_PALADIN;
        case CLASS_HUNTER:
            return SPELLFAMILY_HUNTER;
        case CLASS_DRUID:
            return SPELLFAMILY_DRUID;
        case CLASS_SHAMAN:
            return SPELLFAMILY_SHAMAN;
        case CLASS_WARLOCK:
            return SPELLFAMILY_WARLOCK;
        default:
            return SPELLFAMILY_GENERIC;
        }
    }
};

// Add all scripts in one
void AddSC_mod_challenge_modes()
{
    new ChallengeModes_WorldScript();
    new gobject_challenge_modes();
    new ChallengeMode_Hardcore();
    new ChallengeMode_SemiHardcore();
    new ChallengeMode_SelfCrafted();
    new ChallengeMode_ItemQualityLevel();
    new ChallengeMode_SlowXpGain();
    new ChallengeMode_VerySlowXpGain();
    new ChallengeMode_TurtleMode();
    new ChallengeMode_QuestXpOnly();
    new ChallengeMode_IronMan();
    new ChallengeMode_Pacifist();
    new ChallengeMode_Questless();
    new ChallengeMode_Cashless();
    new ChallengeMode_Commands();
}
