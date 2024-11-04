/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ChallengeModes.h"
#include "SpellMgr.h"
#include "Player.h"
#include "Chat.h"
#include "Config.h"
#include "ScriptMgr.h"
#include "SpellInfo.h"
#include "WorldSession.h"
#include "CommandScript.h"

using namespace Acore::ChatCommands;

ChallengeModes::ChallengeModes() 
{

}

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

class Challenge_CommandScript : public CommandScript
{
public:
    Challenge_CommandScript() : CommandScript("Challenge_CommandScript") { }

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable challengeCommandTable = 
        {
            { "status", HandleChallengeStatusCommand, SEC_PLAYER, Console::No },
            { "enable", HandleChallengeEnableCommand, SEC_ADMINISTRATOR, Console::No },
            { "disable", HandleChallengeDisableCommand, SEC_ADMINISTRATOR, Console::No },
            { "talents", HandleChallengeTalentPointsCommand, SEC_ADMINISTRATOR, Console::No }
        };

        static ChatCommandTable commandTable =
        {
            { "challenge", challengeCommandTable }
        };

        return commandTable;
    }

    static bool HandleChallengeStatusCommand(ChatHandler* handler)
    {
        Player* targetPlayer = handler->getSelectedPlayerOrSelf();

        handler->PSendSysMessage("Challenge mode information for: " + std::string(targetPlayer->GetPlayerName()));

        if (sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, targetPlayer))
        {
            handler->PSendSysMessage("Iron Man Mode is ENABLED.");
        }
        else
        {
            handler->PSendSysMessage("Iron Man Mode is disabled.");
        }
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_HARDCORE, targetPlayer))
        {
            handler->PSendSysMessage("Hardcore Mode is ENABLED.");
        }
        else
        {
            handler->PSendSysMessage("Hardcore Mode is disabled.");
        }
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_SEMI_HARDCORE, targetPlayer))
        {
            handler->PSendSysMessage("Semi-Hardcore Mode is ENABLED.");
        }
        else
        {
            handler->PSendSysMessage("Semi-Hardcore Mode is disabled.");
        }
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_CASHLESS, targetPlayer))
        {
            handler->PSendSysMessage("Cashless Mode is ENABLED.");
        }
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_ITEM_QUALITY_LEVEL, targetPlayer))
        {
            handler->PSendSysMessage("Low Quality Items is ENABLED.");
        }
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_PACIFIST, targetPlayer))
        {
            handler->PSendSysMessage("Pacifist is ENABLED.");
        }
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_QUEST_XP_ONLY, targetPlayer))
        {
            handler->PSendSysMessage("Quest XP Only is ENABLED.");
        }
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_QUESTLESS, targetPlayer))
        {
            handler->PSendSysMessage("Questless mode is ENABLED.");
        }
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_SELF_CRAFTED, targetPlayer))
        {
            handler->PSendSysMessage("Self Crafted is ENABLED.");
        }
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_SLOW_XP_GAIN, targetPlayer))
        {
            handler->PSendSysMessage("Slow XP is ENABLED.");
        }
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_TURTLE_MODE, targetPlayer))
        {
            handler->PSendSysMessage("Very Very Very Slow mode is ENABLED.");
        }
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_VERY_SLOW_XP_GAIN, targetPlayer))
        {
            handler->PSendSysMessage("Very Slow mode is ENABLED.");
        }
        return true;
    }

    static bool HandleChallengeEnableCommand(ChatHandler* handler, char const* args)
    {
        Player* targetPlayer = handler->getSelectedPlayerOrSelf();
        if (!args || !*args)
        {
            handler->PSendSysMessage("Please provide a valid challenge mode setting (0-12) to enable.");
            return false;
        }

        int setting = atoi(args);
        if (setting < 0 || setting > 12)
        {
            handler->PSendSysMessage("Invalid setting. Please enter a number between 0 and 12.");
            return false;
        }

        // Cast integer to ChallengeModeSettings and enable for the player
        ChallengeModeSettings challengeSetting = static_cast<ChallengeModeSettings>(setting);
        targetPlayer->UpdatePlayerSetting("mod-challenge-modes", challengeSetting, 1);

        std::string message = "Challenge mode " + GetChallengeModeName(challengeSetting) + " enabled for " + targetPlayer->GetName() + ".";
        handler->PSendSysMessage(message.c_str());

        return true;
    }

    static bool HandleChallengeDisableCommand(ChatHandler* handler, char const* args)
    {
        Player* targetPlayer = handler->getSelectedPlayerOrSelf();
        if (!args || !*args)
        {
            handler->PSendSysMessage("Please provide a valid challenge mode setting (0-12) to disable.");
            return false;
        }

        int setting = atoi(args);
        if (setting < 0 || setting > 12)
        {
            handler->PSendSysMessage("Invalid setting. Please enter a number between 0 and 12.");
            return false;
        }

        // Cast integer to ChallengeModeSettings and disable for the player
        ChallengeModeSettings challengeSetting = static_cast<ChallengeModeSettings>(setting);
        targetPlayer->UpdatePlayerSetting("mod-challenge-modes", challengeSetting, 0);

        std::string message = "Challenge mode " + GetChallengeModeName(challengeSetting) + " disabled for " + targetPlayer->GetName() + ".";
        handler->PSendSysMessage(message.c_str());

        return true;
    }

    static bool HandleChallengeTalentPointsCommand(ChatHandler* handler)
    {
        Player* targetPlayer = handler->getSelectedPlayerOrSelf();
        uint32 totalTalentPoints = 0;
        uint8  playerLevel = handler->getSelectedPlayerOrSelf()->GetLevel();

        for (int setting = SETTING_HARDCORE; setting <= SETTING_CASHLESS; ++setting)
        {
            ChallengeModeSettings challengeSetting = static_cast<ChallengeModeSettings>(setting);
            if (const auto* talentMap = sChallengeModes->getTalentMapForChallenge(challengeSetting))
            {
                // Check each level and add points if player's level meets/exceeds it
                for (const auto& [level, points] : *talentMap)
                {
                    if (playerLevel >= level && sChallengeModes->challengeEnabledForPlayer(challengeSetting, targetPlayer))
                    {
                        totalTalentPoints += points;
                    }
                }
            }
        }

        std::string message = "Total bonus challenge talent points: " + std::to_string(totalTalentPoints);
        handler->PSendSysMessage(message.c_str());

        return true;
    }
    
    static std::string GetChallengeModeName(ChallengeModeSettings setting)
    {
        switch (setting)
        {
            case SETTING_HARDCORE:           return "Hardcore Mode";
            case SETTING_SEMI_HARDCORE:      return "Semi-Hardcore Mode";
            case SETTING_SELF_CRAFTED:       return "Self-Crafted Mode";
            case SETTING_ITEM_QUALITY_LEVEL: return "Low Quality Item Mode";
            case SETTING_SLOW_XP_GAIN:       return "Slow XP Mode";
            case SETTING_VERY_SLOW_XP_GAIN:  return "Very Slow XP Mode";
            case SETTING_TURTLE_MODE:        return "Very Very Very Slow Mode";
            case SETTING_QUEST_XP_ONLY:      return "Quest XP Only Mode";
            case SETTING_IRON_MAN:           return "Iron Man Mode";
            case HARDCORE_DEAD:              return "Hardcore Deadlock";
            case SETTING_PACIFIST:           return "Pacifist Mode";
            case SETTING_QUESTLESS:          return "Questless Mode";
            case SETTING_CASHLESS:           return "Cashless Mode";
            default:                         return "Unknown Mode";
        }
    }

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

class ChallengeMode_Pacifist_Rewards : public ChallengeMode
{
public:
    ChallengeMode_Pacifist_Rewards() : ChallengeMode("ChallengeMode_Pacifist_Rewards", SETTING_PACIFIST){}

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
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
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_CASHLESS, player)) 
        {
            if (amount > 0)
            {
                amount = 0; // Prevent any money from being gained
            }
        }
    }

    void OnBeforeLootMoney(Player* player, Loot* loot)
    {
        if( loot && loot->loot_type == LOOT_PICKPOCKETING ) 
        {
            loot->gold = loot->gold * 10;
        }
    }

    void OnLevelChanged(Player* player, uint8 oldLevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldLevel);
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
    new ChallengeMode_Pacifist_Rewards();
    new ChallengeMode_Questless();
    new ChallengeMode_Cashless();
    new Challenge_CommandScript();
}
