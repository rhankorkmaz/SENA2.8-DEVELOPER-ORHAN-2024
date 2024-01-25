/*
 Navicat Premium Data Transfer

 Source Server         : ORHAN LOCALHOST MT2
 Source Server Type    : MySQL
 Source Server Version : 50713
 Source Host           : localhost:3306
 Source Schema         : 12sky2sql2

 Target Server Type    : MySQL
 Target Server Version : 50713
 File Encoding         : 65001

 Date: 24/01/2024 10:27:36
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for allavatarinfo
-- ----------------------------
DROP TABLE IF EXISTS `allavatarinfo`;
CREATE TABLE `allavatarinfo`  (
  `LogDate` datetime(0) NULL DEFAULT NULL,
  `World` varchar(6) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `uID` varchar(25) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `aName` varchar(25) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `aTribe` smallint(6) NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for autouserlist
-- ----------------------------
DROP TABLE IF EXISTS `autouserlist`;
CREATE TABLE `autouserlist`  (
  `aDate` datetime(0) NULL DEFAULT NULL,
  `tID` int(11) NULL DEFAULT NULL,
  `tAvatarName` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `tWorldNumber` varchar(14) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `tZoneNumber` int(11) NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for avatarinfo
-- ----------------------------
DROP TABLE IF EXISTS `avatarinfo`;
CREATE TABLE `avatarinfo`  (
  `aCreate` datetime(0) NULL DEFAULT NULL,
  `uID` varchar(12) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `aVisibleState` int(11) NULL DEFAULT 0,
  `aSpecialState` int(11) NULL DEFAULT 0,
  `aPlayTime1` int(11) NULL DEFAULT 0,
  `aPlayTime2` int(11) NULL DEFAULT 0,
  `aKillOtherTribe` int(11) NULL DEFAULT 0,
  `aWorldNumber` int(11) NULL DEFAULT 0,
  `aName` varchar(24) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `aTribe` int(11) NULL DEFAULT 0,
  `aPreviousTribe` int(11) NULL DEFAULT 0,
  `aGender` int(11) NULL DEFAULT 0,
  `aHeadType` int(11) NULL DEFAULT 0,
  `aFaceType` int(11) NULL DEFAULT 0,
  `aLevel1` int(11) NULL DEFAULT 0,
  `aLevel2` int(11) NULL DEFAULT 0,
  `aGeneralExperience1` int(11) NULL DEFAULT 0,
  `aGeneralExperience2` int(11) NULL DEFAULT 0,
  `aVitality` int(11) NULL DEFAULT 0,
  `aStrength` int(11) NULL DEFAULT 0,
  `aKi` int(11) NULL DEFAULT 0,
  `aWisdom` int(11) NULL DEFAULT 0,
  `aEatLifePotion` int(11) NULL DEFAULT 0,
  `aEatManaPotion` int(11) NULL DEFAULT 0,
  `AgiElx` int(11) NULL DEFAULT NULL,
  `StrElx` int(11) NULL DEFAULT NULL,
  `AttAtakElixir` int(11) NULL DEFAULT 0,
  `AttDefElixir` int(11) NULL DEFAULT 0,
  `aStateBonusPoint` int(11) NULL DEFAULT 0,
  `aSkillPoint` int(11) NULL DEFAULT NULL,
  `aEquip` varbinary(5000) NULL DEFAULT NULL,
  `aExpandInventoryDate` int(11) NULL DEFAULT NULL,
  `aMoney` int(11) NULL DEFAULT 0,
  `aInventory` varbinary(10000) NULL DEFAULT NULL,
  `aTradeMoney` int(11) NULL DEFAULT 0,
  `aTrade` varbinary(5000) NULL DEFAULT NULL,
  `aExpandStoreDate` int(11) NULL DEFAULT NULL,
  `aStoreMoney` int(11) NULL DEFAULT 0,
  `aStoreItem` varbinary(5000) NULL DEFAULT NULL,
  `aSkill` varbinary(1000) NULL DEFAULT NULL,
  `aHotKey` varbinary(1000) NULL DEFAULT NULL,
  `aQuestInfo` varbinary(1000) NULL DEFAULT NULL,
  `aFriend` varbinary(1000) NULL DEFAULT NULL,
  `aTeacher` varbinary(1000) NULL DEFAULT NULL,
  `aStudent` varbinary(1000) NULL DEFAULT NULL,
  `aTeacherPoint` int(11) NULL DEFAULT NULL,
  `aGuildName` varbinary(1000) NULL DEFAULT NULL,
  `aGuildRole` int(11) NULL DEFAULT NULL,
  `aCallName` varbinary(5000) NULL DEFAULT NULL,
  `aGuildMarkNum` int(11) NULL DEFAULT NULL,
  `aGuildMarkEffect` int(11) NULL DEFAULT NULL,
  `aLogoutInfo01` int(11) NULL DEFAULT NULL,
  `aLogoutInfo02` int(11) NULL DEFAULT NULL,
  `aLogoutInfo03` int(11) NULL DEFAULT NULL,
  `aLogoutInfo04` int(11) NULL DEFAULT NULL,
  `aLogoutInfo05` int(11) NULL DEFAULT NULL,
  `aLogoutInfo06` int(11) NULL DEFAULT NULL,
  `ProtectionScroll` int(11) NULL DEFAULT NULL,
  `ProtectionCharm` int(11) NULL DEFAULT NULL,
  `HolyWater` int(11) NULL DEFAULT NULL,
  `SuperiorPill` int(11) NULL DEFAULT NULL,
  `ScrollofLoyality` int(11) NULL DEFAULT NULL,
  `ScrollofBattle` int(11) NULL DEFAULT NULL,
  `GodTempleKey` int(11) NULL DEFAULT NULL,
  `SolemGrounds` int(11) NULL DEFAULT NULL,
  `EdgeOfTaiyan` int(11) NULL DEFAULT NULL,
  `ScrollOfSeekers` int(11) NULL DEFAULT NULL,
  `aKillMonsterNum` int(11) NULL DEFAULT 0,
  `RankPoint` int(11) NULL DEFAULT 0,
  `RankPrize` int(11) NULL DEFAULT 0,
  `aSearch` int(11) NULL DEFAULT NULL,
  `ExchangeHealtiks` int(11) NULL DEFAULT NULL,
  `ExchangeChiiks` int(11) NULL DEFAULT NULL,
  `aTribeVoteDate` int(11) NULL DEFAULT NULL,
  `HealtAutoPot` int(11) NULL DEFAULT NULL,
  `ManaAutoPot` int(11) NULL DEFAULT NULL,
  `aAnimal01` int(11) NULL DEFAULT NULL,
  `aAnimal02` int(11) NULL DEFAULT NULL,
  `aAnimal03` int(11) NULL DEFAULT NULL,
  `aAnimal04` int(11) NULL DEFAULT NULL,
  `aAnimal05` int(11) NULL DEFAULT NULL,
  `aAnimal06` int(11) NULL DEFAULT NULL,
  `aAnimal07` int(11) NULL DEFAULT NULL,
  `aAnimal08` int(11) NULL DEFAULT NULL,
  `aAnimal09` int(11) NULL DEFAULT NULL,
  `aAnimal10` int(11) NULL DEFAULT NULL,
  `aAnimalIndex` int(11) NULL DEFAULT NULL,
  `aAnimalTime` int(11) NULL DEFAULT NULL,
  `LuckyCombine` int(11) NULL DEFAULT NULL,
  `LuckyUpgrade` int(11) NULL DEFAULT NULL,
  `LuckyDrop` int(11) NULL DEFAULT NULL,
  `Title` int(11) NULL DEFAULT NULL,
  `ExtinctionScroll` int(11) NULL DEFAULT NULL,
  `aUpradgeValue` int(11) NULL DEFAULT NULL,
  `Beginner` int(11) NULL DEFAULT NULL,
  `BeginnerLevel` int(11) NULL DEFAULT 0,
  `OnlineHour` int(11) NULL DEFAULT NULL,
  `Cppc` int(11) NULL DEFAULT NULL,
  `iUseOrnament` int(11) NULL DEFAULT NULL,
  `iSilverOrnamentRemainsTime` int(11) NULL DEFAULT NULL,
  `IslandOfBlood` int(11) NULL DEFAULT NULL,
  `IslandOfSoulMReal1` int(11) NULL DEFAULT NULL,
  `IslandOfSoulMReal2` int(11) NULL DEFAULT NULL,
  `IslandOfSoulMReal3` int(11) NULL DEFAULT NULL,
  `IslandOfSoulMReal4` int(11) NULL DEFAULT NULL,
  `IslandOfSoulMReal5` int(11) NULL DEFAULT NULL,
  `IslandOfSoulMReal6` int(11) NULL DEFAULT NULL,
  `SkillIncreaseCritHit` int(11) NULL DEFAULT NULL,
  `LifeOrDeath` int(11) NULL DEFAULT NULL,
  `iGoldOrnamentRemainsTime` int(11) NULL DEFAULT NULL,
  `BloodBoost` int(11) NULL DEFAULT NULL,
  `SoulBoost` int(11) NULL DEFAULT NULL,
  `Registration` int(11) NULL DEFAULT NULL,
  `ExpPill` int(11) NULL DEFAULT 0,
  `FactReturnScroll` int(11) NULL DEFAULT NULL,
  `PetExpBoost` int(11) NULL DEFAULT NULL,
  `Costume1` int(11) NULL DEFAULT NULL,
  `Costume2` int(11) NULL DEFAULT NULL,
  `Costume3` int(11) NULL DEFAULT NULL,
  `Costume4` int(11) NULL DEFAULT NULL,
  `Costume5` int(11) NULL DEFAULT NULL,
  `Costume6` int(11) NULL DEFAULT NULL,
  `Costume7` int(11) NULL DEFAULT NULL,
  `Costume8` int(11) NULL DEFAULT NULL,
  `Costume9` int(11) NULL DEFAULT NULL,
  `Costume10` int(11) NULL DEFAULT NULL,
  `CostumeInventory1` int(11) NULL DEFAULT NULL,
  `CostumeInventory2` int(11) NULL DEFAULT NULL,
  `CostumeInventory3` int(11) NULL DEFAULT NULL,
  `CostumeInventory4` int(11) NULL DEFAULT NULL,
  `CostumeInventory5` int(11) NULL DEFAULT NULL,
  `CostumeInventory6` int(11) NULL DEFAULT NULL,
  `CostumeInventory7` int(11) NULL DEFAULT NULL,
  `CostumeInventory8` int(11) NULL DEFAULT NULL,
  `CostumeInventory9` int(11) NULL DEFAULT NULL,
  `CostumeInventory10` int(11) NULL DEFAULT NULL,
  `SelectCostume` int(11) NULL DEFAULT NULL,
  `DamegeBoostScroll` int(11) NULL DEFAULT NULL,
  `HealtBoostScroll` int(11) NULL DEFAULT NULL,
  `CritBoostScroll` int(11) NULL DEFAULT NULL,
  `AutoBuffScroll` int(11) NULL DEFAULT NULL,
  `AutoBuffSmenu` varbinary(1000) NULL DEFAULT NULL,
  `FishBread` int(11) NULL DEFAULT NULL,
  `SweetPateto` int(11) NULL DEFAULT NULL,
  `InventorySocket` varbinary(10000) NULL DEFAULT NULL,
  `EquipSocket` varbinary(3000) NULL DEFAULT NULL,
  `TradeSocket` varbinary(3000) NULL DEFAULT NULL,
  `StoreSocket` varbinary(3000) NULL DEFAULT NULL,
  `Hunt7d` int(11) NULL DEFAULT NULL,
  `Hunt5h` int(11) NULL DEFAULT NULL,
  `Inventorybar` int(11) NULL DEFAULT NULL,
  `TradeBar` int(11) NULL DEFAULT NULL,
  `BankBar` int(11) NULL DEFAULT NULL,
  `RebirtHall` int(11) NULL DEFAULT NULL,
  `PreServeCharm` int(11) NULL DEFAULT NULL,
  `Chenjoho` int(11) NULL DEFAULT NULL,
  `aRankPoint` int(11) NULL DEFAULT 0,
  `aRank` int(11) NULL DEFAULT NULL,
  `FanctionNoticeScroll` int(11) NULL DEFAULT NULL,
  `AnimalExp` varbinary(200) NULL DEFAULT NULL,
  `AnimalStat` varbinary(200) NULL DEFAULT NULL,
  `DoubleMouthExp2x` int(11) NULL DEFAULT NULL,
  `VigilanteScroll` int(11) NULL DEFAULT 0,
  `RafflaTicket` int(11) NULL DEFAULT 0,
  `MountAbsorb` int(11) NULL DEFAULT 0,
  `MountAbsorbe` int(11) NULL DEFAULT 0,
  `DamageIcreaseSolUst` int(11) NULL DEFAULT 0,
  `BurstPill` int(11) NULL DEFAULT 0,
  `RagePill` int(11) NULL DEFAULT NULL,
  `WarriorScroll` int(11) NULL DEFAULT 0,
  `HeroPill` int(11) NULL DEFAULT NULL,
  `WingProtectionRune` int(11) NULL DEFAULT NULL,
  `LessDecressScroll` int(11) NULL DEFAULT NULL,
  `PetInventory` int(11) NULL DEFAULT NULL,
  `PetInventoryTick` varbinary(200) NULL DEFAULT NULL,
  `JoinWar` int(11) NULL DEFAULT 0,
  `PlayerKill` int(11) NULL DEFAULT 0,
  `MonsterKill` int(11) NULL DEFAULT 0,
  `PlayTimeDay` int(11) NULL DEFAULT 0,
  `AutoHuntConfing` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT '',
  `BloodStained` int(11) NULL DEFAULT 0,
  `FishingTime` int(11) NULL DEFAULT 0,
  `BottleIndex` int(11) NULL DEFAULT 0,
  `BottleTime` int(11) NULL DEFAULT 0,
  `Bottle1` int(11) NULL DEFAULT 0,
  `Bottle2` int(11) NULL DEFAULT 0,
  `Bottle3` int(11) NULL DEFAULT 0,
  `Bottle4` int(11) NULL DEFAULT 0,
  `Bottle5` int(11) NULL DEFAULT 0,
  `Bottle6` int(11) NULL DEFAULT 0,
  `Bottle7` int(11) NULL DEFAULT 0,
  `Bottle8` int(11) NULL DEFAULT 0,
  `Bottle9` int(11) NULL DEFAULT 0,
  `Bottle10` int(11) NULL DEFAULT 0,
  `BottlePrice1` int(11) NULL DEFAULT 0,
  `BottlePrice2` int(11) NULL DEFAULT 0,
  `BottlePrice3` int(11) NULL DEFAULT 0,
  `BottlePrice4` int(11) NULL DEFAULT 0,
  `BottlePrice5` int(11) NULL DEFAULT 0,
  `BottlePrice6` int(11) NULL DEFAULT 0,
  `BottlePrice7` int(11) NULL DEFAULT 0,
  `BottlePrice8` int(11) NULL DEFAULT 0,
  `BottlePrice9` int(11) NULL DEFAULT 0,
  `BottlePrice10` int(11) NULL DEFAULT 0,
  `OtherSkill1` int(11) NULL DEFAULT 0,
  `OtherSkill2` int(11) NULL DEFAULT 0,
  `OtherSkill3` int(11) NULL DEFAULT 0,
  `OtherSkill4` int(11) NULL DEFAULT 0,
  `OtherSkill5` int(11) NULL DEFAULT 0,
  `OtherSkill6` int(11) NULL DEFAULT 0,
  `OtherSkill7` int(11) NULL DEFAULT 0,
  `OtherSkill8` int(11) NULL DEFAULT 0,
  `OtherSkill9` int(11) NULL DEFAULT 0,
  `OtherSkill10` int(11) NULL DEFAULT 0,
  `OtherSkill11` int(11) NULL DEFAULT 0,
  `OtherSkill12` int(11) NULL DEFAULT 0,
  `OtherSkill13` int(11) NULL DEFAULT 0,
  `OtherSkill14` int(11) NULL DEFAULT 0,
  `OtherSkillState11` int(11) NULL DEFAULT 0,
  `OtherSkillState12` int(11) NULL DEFAULT 0,
  `OtherSkillState13` int(11) NULL DEFAULT 0,
  `OtherSkillState14` int(11) NULL DEFAULT 0,
  `OtherSkillState15` int(11) NULL DEFAULT 0,
  `OtherSkillState16` int(11) NULL DEFAULT 0,
  `OtherSkillState17` int(11) NULL DEFAULT 0,
  `OtherSkillState18` int(11) NULL DEFAULT 0,
  `OtherSkillState19` int(11) NULL DEFAULT 0,
  `OtherSkillState110` int(11) NULL DEFAULT 0,
  `OtherSkillState111` int(11) NULL DEFAULT 0,
  `OtherSkillState112` int(11) NULL DEFAULT 0,
  `OtherSkillState113` int(11) NULL DEFAULT 0,
  `OtherSkillState114` int(11) NULL DEFAULT 0,
  `OtherSkillSolUst` int(11) NULL DEFAULT 0,
  `Fury` int(11) NULL DEFAULT 0,
  `Premium` int(11) NULL DEFAULT 0,
  `HideCostumeRegister` int(11) NULL DEFAULT 0,
  `BuffDurationPill` int(11) NULL DEFAULT 0,
  UNIQUE INDEX `aName`(`aName`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = gb2312 COLLATE = gb2312_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for avatarinfocreatelog
-- ----------------------------
DROP TABLE IF EXISTS `avatarinfocreatelog`;
CREATE TABLE `avatarinfocreatelog`  (
  `LogDate` datetime(0) NULL DEFAULT NULL,
  `RCount` int(11) NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for avatarnameinfo
-- ----------------------------
DROP TABLE IF EXISTS `avatarnameinfo`;
CREATE TABLE `avatarnameinfo`  (
  `aDate` datetime(0) NULL DEFAULT NULL,
  `aName` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = gb2312 COLLATE = gb2312_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for baduserinfo
-- ----------------------------
DROP TABLE IF EXISTS `baduserinfo`;
CREATE TABLE `baduserinfo`  (
  `bDate` datetime(0) NULL DEFAULT NULL,
  `uID` varchar(24) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `uWarningNum` int(11) NULL DEFAULT 0
) ENGINE = InnoDB CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for baduserlist
-- ----------------------------
DROP TABLE IF EXISTS `baduserlist`;
CREATE TABLE `baduserlist`  (
  `bDate` datetime(0) NULL DEFAULT NULL,
  `tID` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `tSort` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `tHackName` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for bonusinfo
-- ----------------------------
DROP TABLE IF EXISTS `bonusinfo`;
CREATE TABLE `bonusinfo`  (
  `uID` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `aName` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `aLevel` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for comments
-- ----------------------------
DROP TABLE IF EXISTS `comments`;
CREATE TABLE `comments`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `news_id` int(11) NOT NULL,
  `name` varchar(255) CHARACTER SET latin7 COLLATE latin7_bin NOT NULL,
  `message` text CHARACTER SET latin7 COLLATE latin7_bin NOT NULL,
  `created_at` timestamp(0) NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `news_id`(`news_id`) USING BTREE,
  CONSTRAINT `comments_ibfk_1` FOREIGN KEY (`news_id`) REFERENCES `news` (`id`) ON DELETE CASCADE ON UPDATE RESTRICT
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = latin7 COLLATE = latin7_bin ROW_FORMAT = Compact;

-- ----------------------------
-- Table structure for definemaxusernum
-- ----------------------------
DROP TABLE IF EXISTS `definemaxusernum`;
CREATE TABLE `definemaxusernum`  (
  `mMaxUserNum` int(11) NULL DEFAULT NULL,
  `mAddPlayerNum` int(11) NULL DEFAULT NULL,
  `mGageUserNum` int(11) NULL DEFAULT NULL,
  `mAddUserNum` int(11) NULL DEFAULT NULL,
  `aWorldNumber` int(11) NULL DEFAULT NULL
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_unicode_ci ROW_FORMAT = Fixed;

-- ----------------------------
-- Table structure for deleteavatarinfo
-- ----------------------------
DROP TABLE IF EXISTS `deleteavatarinfo`;
CREATE TABLE `deleteavatarinfo`  (
  `aCreate` datetime(0) NULL DEFAULT NULL,
  `uID` varchar(12) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `aVisibleState` int(11) NULL DEFAULT 0,
  `aSpecialState` int(11) NULL DEFAULT 0,
  `aPlayTime1` int(11) NULL DEFAULT 0,
  `aPlayTime2` int(11) NULL DEFAULT 0,
  `aKillOtherTribe` int(11) NULL DEFAULT 0,
  `aWorldNumber` int(11) NULL DEFAULT 0,
  `aName` varchar(24) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `aTribe` int(11) NULL DEFAULT 0,
  `aPreviousTribe` int(11) NULL DEFAULT 0,
  `aGender` int(11) NULL DEFAULT 0,
  `aHeadType` int(11) NULL DEFAULT 0,
  `aFaceType` int(11) NULL DEFAULT 0,
  `aLevel1` int(11) NULL DEFAULT 0,
  `aLevel2` int(11) NULL DEFAULT 0,
  `aGeneralExperience1` int(11) NULL DEFAULT 0,
  `aGeneralExperience2` int(11) NULL DEFAULT 0,
  `aVitality` int(11) NULL DEFAULT 0,
  `aStrength` int(11) NULL DEFAULT 0,
  `aKi` int(11) NULL DEFAULT 0,
  `aWisdom` int(11) NULL DEFAULT 0,
  `aEatLifePotion` int(11) NULL DEFAULT 0,
  `aEatManaPotion` int(11) NULL DEFAULT 0,
  `AgiElx` int(11) NULL DEFAULT NULL,
  `StrElx` int(11) NULL DEFAULT NULL,
  `AttAtakElixir` int(11) NULL DEFAULT 0,
  `AttDefElixir` int(11) NULL DEFAULT 0,
  `aStateBonusPoint` int(11) NULL DEFAULT 0,
  `aSkillPoint` int(11) NULL DEFAULT NULL,
  `aEquip` varbinary(5000) NULL DEFAULT NULL,
  `aExpandInventoryDate` int(11) NULL DEFAULT NULL,
  `aMoney` int(11) NULL DEFAULT 0,
  `aInventory` varbinary(10000) NULL DEFAULT NULL,
  `aTradeMoney` int(11) NULL DEFAULT 0,
  `aTrade` varbinary(5000) NULL DEFAULT NULL,
  `aExpandStoreDate` int(11) NULL DEFAULT NULL,
  `aStoreMoney` int(11) NULL DEFAULT 0,
  `aStoreItem` varbinary(5000) NULL DEFAULT NULL,
  `aSkill` varbinary(1000) NULL DEFAULT NULL,
  `aHotKey` varbinary(1000) NULL DEFAULT NULL,
  `aQuestInfo` varbinary(1000) NULL DEFAULT NULL,
  `aFriend` varbinary(1000) NULL DEFAULT NULL,
  `aTeacher` varbinary(1000) NULL DEFAULT NULL,
  `aStudent` varbinary(1000) NULL DEFAULT NULL,
  `aTeacherPoint` int(11) NULL DEFAULT NULL,
  `aGuildName` varbinary(1000) NULL DEFAULT NULL,
  `aGuildRole` int(11) NULL DEFAULT NULL,
  `aCallName` varbinary(5000) NULL DEFAULT NULL,
  `aGuildMarkNum` int(11) NULL DEFAULT NULL,
  `aGuildMarkEffect` int(11) NULL DEFAULT NULL,
  `aLogoutInfo01` int(11) NULL DEFAULT NULL,
  `aLogoutInfo02` int(11) NULL DEFAULT NULL,
  `aLogoutInfo03` int(11) NULL DEFAULT NULL,
  `aLogoutInfo04` int(11) NULL DEFAULT NULL,
  `aLogoutInfo05` int(11) NULL DEFAULT NULL,
  `aLogoutInfo06` int(11) NULL DEFAULT NULL,
  `ProtectionScroll` int(11) NULL DEFAULT NULL,
  `ProtectionCharm` int(11) NULL DEFAULT NULL,
  `HolyWater` int(11) NULL DEFAULT NULL,
  `SuperiorPill` int(11) NULL DEFAULT NULL,
  `ScrollofLoyality` int(11) NULL DEFAULT NULL,
  `ScrollofBattle` int(11) NULL DEFAULT NULL,
  `GodTempleKey` int(11) NULL DEFAULT NULL,
  `SolemGrounds` int(11) NULL DEFAULT NULL,
  `EdgeOfTaiyan` int(11) NULL DEFAULT NULL,
  `ScrollOfSeekers` int(11) NULL DEFAULT NULL,
  `aKillMonsterNum` int(11) NULL DEFAULT 0,
  `RankPoint` int(11) NULL DEFAULT 0,
  `RankPrize` int(11) NULL DEFAULT 0,
  `aSearch` int(11) NULL DEFAULT NULL,
  `ExchangeHealtiks` int(11) NULL DEFAULT NULL,
  `ExchangeChiiks` int(11) NULL DEFAULT NULL,
  `aTribeVoteDate` int(11) NULL DEFAULT NULL,
  `HealtAutoPot` int(11) NULL DEFAULT NULL,
  `ManaAutoPot` int(11) NULL DEFAULT NULL,
  `aAnimal01` int(11) NULL DEFAULT NULL,
  `aAnimal02` int(11) NULL DEFAULT NULL,
  `aAnimal03` int(11) NULL DEFAULT NULL,
  `aAnimal04` int(11) NULL DEFAULT NULL,
  `aAnimal05` int(11) NULL DEFAULT NULL,
  `aAnimal06` int(11) NULL DEFAULT NULL,
  `aAnimal07` int(11) NULL DEFAULT NULL,
  `aAnimal08` int(11) NULL DEFAULT NULL,
  `aAnimal09` int(11) NULL DEFAULT NULL,
  `aAnimal10` int(11) NULL DEFAULT NULL,
  `aAnimalIndex` int(11) NULL DEFAULT NULL,
  `aAnimalTime` int(11) NULL DEFAULT NULL,
  `LuckyCombine` int(11) NULL DEFAULT NULL,
  `LuckyUpgrade` int(11) NULL DEFAULT NULL,
  `LuckyDrop` int(11) NULL DEFAULT NULL,
  `Title` int(11) NULL DEFAULT NULL,
  `ExtinctionScroll` int(11) NULL DEFAULT NULL,
  `aUpradgeValue` int(11) NULL DEFAULT NULL,
  `Beginner` int(11) NULL DEFAULT NULL,
  `BeginnerLevel` int(11) NULL DEFAULT 0,
  `OnlineHour` int(11) NULL DEFAULT NULL,
  `Cppc` int(11) NULL DEFAULT NULL,
  `iUseOrnament` int(11) NULL DEFAULT NULL,
  `iSilverOrnamentRemainsTime` int(11) NULL DEFAULT NULL,
  `IslandOfBlood` int(11) NULL DEFAULT NULL,
  `IslandOfSoulMReal1` int(11) NULL DEFAULT NULL,
  `IslandOfSoulMReal2` int(11) NULL DEFAULT NULL,
  `IslandOfSoulMReal3` int(11) NULL DEFAULT NULL,
  `IslandOfSoulMReal4` int(11) NULL DEFAULT NULL,
  `IslandOfSoulMReal5` int(11) NULL DEFAULT NULL,
  `IslandOfSoulMReal6` int(11) NULL DEFAULT NULL,
  `SkillIncreaseCritHit` int(11) NULL DEFAULT NULL,
  `LifeOrDeath` int(11) NULL DEFAULT NULL,
  `iGoldOrnamentRemainsTime` int(11) NULL DEFAULT NULL,
  `BloodBoost` int(11) NULL DEFAULT NULL,
  `SoulBoost` int(11) NULL DEFAULT NULL,
  `Registration` int(11) NULL DEFAULT NULL,
  `ExpPill` int(11) NULL DEFAULT 0,
  `FactReturnScroll` int(11) NULL DEFAULT NULL,
  `PetExpBoost` int(11) NULL DEFAULT NULL,
  `Costume1` int(11) NULL DEFAULT NULL,
  `Costume2` int(11) NULL DEFAULT NULL,
  `Costume3` int(11) NULL DEFAULT NULL,
  `Costume4` int(11) NULL DEFAULT NULL,
  `Costume5` int(11) NULL DEFAULT NULL,
  `Costume6` int(11) NULL DEFAULT NULL,
  `Costume7` int(11) NULL DEFAULT NULL,
  `Costume8` int(11) NULL DEFAULT NULL,
  `Costume9` int(11) NULL DEFAULT NULL,
  `Costume10` int(11) NULL DEFAULT NULL,
  `CostumeInventory1` int(11) NULL DEFAULT NULL,
  `CostumeInventory2` int(11) NULL DEFAULT NULL,
  `CostumeInventory3` int(11) NULL DEFAULT NULL,
  `CostumeInventory4` int(11) NULL DEFAULT NULL,
  `CostumeInventory5` int(11) NULL DEFAULT NULL,
  `CostumeInventory6` int(11) NULL DEFAULT NULL,
  `CostumeInventory7` int(11) NULL DEFAULT NULL,
  `CostumeInventory8` int(11) NULL DEFAULT NULL,
  `CostumeInventory9` int(11) NULL DEFAULT NULL,
  `CostumeInventory10` int(11) NULL DEFAULT NULL,
  `SelectCostume` int(11) NULL DEFAULT NULL,
  `DamegeBoostScroll` int(11) NULL DEFAULT NULL,
  `HealtBoostScroll` int(11) NULL DEFAULT NULL,
  `CritBoostScroll` int(11) NULL DEFAULT NULL,
  `AutoBuffScroll` int(11) NULL DEFAULT NULL,
  `AutoBuffSmenu` varbinary(1000) NULL DEFAULT NULL,
  `FishBread` int(11) NULL DEFAULT NULL,
  `SweetPateto` int(11) NULL DEFAULT NULL,
  `InventorySocket` varbinary(10000) NULL DEFAULT NULL,
  `EquipSocket` varbinary(3000) NULL DEFAULT NULL,
  `TradeSocket` varbinary(3000) NULL DEFAULT NULL,
  `StoreSocket` varbinary(3000) NULL DEFAULT NULL,
  `Hunt7d` int(11) NULL DEFAULT NULL,
  `Hunt5h` int(11) NULL DEFAULT NULL,
  `Inventorybar` int(11) NULL DEFAULT NULL,
  `TradeBar` int(11) NULL DEFAULT NULL,
  `BankBar` int(11) NULL DEFAULT NULL,
  `RebirtHall` int(11) NULL DEFAULT NULL,
  `PreServeCharm` int(11) NULL DEFAULT NULL,
  `Chenjoho` int(11) NULL DEFAULT NULL,
  `aRankPoint` int(11) NULL DEFAULT 0,
  `aRank` int(11) NULL DEFAULT NULL,
  `FanctionNoticeScroll` int(11) NULL DEFAULT NULL,
  `AnimalExp` varbinary(200) NULL DEFAULT NULL,
  `AnimalStat` varbinary(200) NULL DEFAULT NULL,
  `DoubleMouthExp2x` int(11) NULL DEFAULT NULL,
  `VigilanteScroll` int(11) NULL DEFAULT 0,
  `RafflaTicket` int(11) NULL DEFAULT 0,
  `MountAbsorb` int(11) NULL DEFAULT 0,
  `MountAbsorbe` int(11) NULL DEFAULT 0,
  `DamageIcreaseSolUst` int(11) NULL DEFAULT 0,
  `BurstPill` int(11) NULL DEFAULT 0,
  `RagePill` int(11) NULL DEFAULT NULL,
  `WarriorScroll` int(11) NULL DEFAULT 0,
  `HeroPill` int(11) NULL DEFAULT NULL,
  `WingProtectionRune` int(11) NULL DEFAULT NULL,
  `LessDecressScroll` int(11) NULL DEFAULT NULL,
  `PetInventory` int(11) NULL DEFAULT NULL,
  `PetInventoryTick` varbinary(200) NULL DEFAULT NULL,
  `JoinWar` int(11) NULL DEFAULT 0,
  `PlayerKill` int(11) NULL DEFAULT 0,
  `MonsterKill` int(11) NULL DEFAULT 0,
  `PlayTimeDay` int(11) NULL DEFAULT 0,
  `AutoHuntConfing` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT '',
  `BloodStained` int(11) NULL DEFAULT 0,
  `FishingTime` int(11) NULL DEFAULT 0,
  `BottleIndex` int(11) NULL DEFAULT 0,
  `BottleTime` int(11) NULL DEFAULT 0,
  `Bottle1` int(11) NULL DEFAULT 0,
  `Bottle2` int(11) NULL DEFAULT 0,
  `Bottle3` int(11) NULL DEFAULT 0,
  `Bottle4` int(11) NULL DEFAULT 0,
  `Bottle5` int(11) NULL DEFAULT 0,
  `Bottle6` int(11) NULL DEFAULT 0,
  `Bottle7` int(11) NULL DEFAULT 0,
  `Bottle8` int(11) NULL DEFAULT 0,
  `Bottle9` int(11) NULL DEFAULT 0,
  `Bottle10` int(11) NULL DEFAULT 0,
  `BottlePrice1` int(11) NULL DEFAULT 0,
  `BottlePrice2` int(11) NULL DEFAULT 0,
  `BottlePrice3` int(11) NULL DEFAULT 0,
  `BottlePrice4` int(11) NULL DEFAULT 0,
  `BottlePrice5` int(11) NULL DEFAULT 0,
  `BottlePrice6` int(11) NULL DEFAULT 0,
  `BottlePrice7` int(11) NULL DEFAULT 0,
  `BottlePrice8` int(11) NULL DEFAULT 0,
  `BottlePrice9` int(11) NULL DEFAULT 0,
  `BottlePrice10` int(11) NULL DEFAULT 0,
  `OtherSkill1` int(11) NULL DEFAULT 0,
  `OtherSkill2` int(11) NULL DEFAULT 0,
  `OtherSkill3` int(11) NULL DEFAULT 0,
  `OtherSkill4` int(11) NULL DEFAULT 0,
  `OtherSkill5` int(11) NULL DEFAULT 0,
  `OtherSkill6` int(11) NULL DEFAULT 0,
  `OtherSkill7` int(11) NULL DEFAULT 0,
  `OtherSkill8` int(11) NULL DEFAULT 0,
  `OtherSkill9` int(11) NULL DEFAULT 0,
  `OtherSkill10` int(11) NULL DEFAULT 0,
  `OtherSkill11` int(11) NULL DEFAULT 0,
  `OtherSkill12` int(11) NULL DEFAULT 0,
  `OtherSkill13` int(11) NULL DEFAULT 0,
  `OtherSkill14` int(11) NULL DEFAULT 0,
  `OtherSkillState11` int(11) NULL DEFAULT 0,
  `OtherSkillState12` int(11) NULL DEFAULT 0,
  `OtherSkillState13` int(11) NULL DEFAULT 0,
  `OtherSkillState14` int(11) NULL DEFAULT 0,
  `OtherSkillState15` int(11) NULL DEFAULT 0,
  `OtherSkillState16` int(11) NULL DEFAULT 0,
  `OtherSkillState17` int(11) NULL DEFAULT 0,
  `OtherSkillState18` int(11) NULL DEFAULT 0,
  `OtherSkillState19` int(11) NULL DEFAULT 0,
  `OtherSkillState110` int(11) NULL DEFAULT 0,
  `OtherSkillState111` int(11) NULL DEFAULT 0,
  `OtherSkillState112` int(11) NULL DEFAULT 0,
  `OtherSkillState113` int(11) NULL DEFAULT 0,
  `OtherSkillState114` int(11) NULL DEFAULT 0,
  `OtherSkillSolUst` int(11) NULL DEFAULT 0,
  `Fury` int(11) NULL DEFAULT 0,
  `Premium` int(11) NULL DEFAULT 0,
  `HideCostumeRegister` int(11) NULL DEFAULT 0,
  `BuffDurationPill` int(11) NULL DEFAULT 0,
  UNIQUE INDEX `aCreate`(`aCreate`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = gb2312 COLLATE = gb2312_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for dtproperties
-- ----------------------------
DROP TABLE IF EXISTS `dtproperties`;
CREATE TABLE `dtproperties`  (
  `id` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `objectid` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `property` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `value` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `uvalue` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `lvalue` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `version` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for event_id_list
-- ----------------------------
DROP TABLE IF EXISTS `event_id_list`;
CREATE TABLE `event_id_list`  (
  `uid` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `eventid` float(10, 5) NULL DEFAULT NULL,
  `aname` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `serverid` float(10, 5) NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for eventinfo
-- ----------------------------
DROP TABLE IF EXISTS `eventinfo`;
CREATE TABLE `eventinfo`  (
  `uID` varchar(12) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `uEventNum01` int(11) NULL DEFAULT 0,
  `uEventNum02` int(11) NULL DEFAULT 0
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for giftinfo
-- ----------------------------
DROP TABLE IF EXISTS `giftinfo`;
CREATE TABLE `giftinfo`  (
  `uID` varchar(50) CHARACTER SET gb2312 COLLATE gb2312_bin NOT NULL DEFAULT '',
  `gData1` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `gNumber1` int(11) NULL DEFAULT NULL,
  `gData2` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `gNumber2` int(11) NULL DEFAULT NULL,
  `gData3` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `gNumber3` int(11) NULL DEFAULT NULL,
  `gData4` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `gNumber4` int(11) NULL DEFAULT NULL,
  `gData5` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `gNumber5` int(11) NULL DEFAULT NULL,
  PRIMARY KEY (`uID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = gb2312 COLLATE = gb2312_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for giftitemlist
-- ----------------------------
DROP TABLE IF EXISTS `giftitemlist`;
CREATE TABLE `giftitemlist`  (
  `gGiftItemSetNumber` int(11) NULL DEFAULT NULL,
  `gGiftItem01` int(11) NULL DEFAULT NULL,
  `gGiftItem01Cnt` int(11) NULL DEFAULT NULL,
  `gGiftItem02` int(11) NULL DEFAULT NULL,
  `gGiftItem02Cnt` int(11) NULL DEFAULT NULL,
  `gGiftItem03` int(11) NULL DEFAULT NULL,
  `gGiftItem03Cnt` int(11) NULL DEFAULT NULL,
  `gGiftItem04` int(11) NULL DEFAULT NULL,
  `gGiftItem04Cnt` int(11) NULL DEFAULT NULL,
  `gGiftItem05` int(11) NULL DEFAULT NULL,
  `gGiftItem05Cnt` int(11) NULL DEFAULT NULL,
  `gGiftItem06` int(11) NULL DEFAULT NULL,
  `gGiftItem06Cnt` int(11) NULL DEFAULT NULL,
  `gGiftItem07` int(11) NULL DEFAULT NULL,
  `gGiftItem07Cnt` int(11) NULL DEFAULT NULL,
  `gGiftItem08` int(11) NULL DEFAULT NULL,
  `gGiftItem08Cnt` int(11) NULL DEFAULT NULL,
  `gGiftItem09` int(11) NULL DEFAULT NULL,
  `gGiftItem09Cnt` int(11) NULL DEFAULT NULL,
  `gGiftItem10` int(11) NULL DEFAULT NULL,
  `gGiftItem10Cnt` int(11) NULL DEFAULT NULL
) ENGINE = MyISAM CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Fixed;

-- ----------------------------
-- Table structure for guildeventhelper
-- ----------------------------
DROP TABLE IF EXISTS `guildeventhelper`;
CREATE TABLE `guildeventhelper`  (
  `startDate` datetime(0) NULL DEFAULT NULL,
  `endDate` datetime(0) NULL DEFAULT NULL,
  `status` int(11) NULL DEFAULT 0
) ENGINE = InnoDB CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for guildeventinfo
-- ----------------------------
DROP TABLE IF EXISTS `guildeventinfo`;
CREATE TABLE `guildeventinfo`  (
  `gName` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `gScore` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for guildinfo
-- ----------------------------
DROP TABLE IF EXISTS `guildinfo`;
CREATE TABLE `guildinfo`  (
  `iDate` datetime(0) NULL DEFAULT NULL,
  `aWorldNumber` int(11) NULL DEFAULT NULL,
  `gName` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `gGrade` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `gMaster01` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `gSubMaster01` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `gSubMaster02` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `gMember` text CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL,
  `gNotice01` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `gNotice02` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `gNotice03` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `gNotice04` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `GuldPoint` int(11) NULL DEFAULT 0,
  `GuldPoint1` int(11) NULL DEFAULT 0,
  `GuildTime` int(11) NULL DEFAULT 0,
  `GuildTime1` int(11) NULL DEFAULT 0,
  `GuildTime2` int(11) NULL DEFAULT 0
) ENGINE = InnoDB CHARACTER SET = gb2312 COLLATE = gb2312_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for hackinfo
-- ----------------------------
DROP TABLE IF EXISTS `hackinfo`;
CREATE TABLE `hackinfo`  (
  `hSize` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for hwidcontrol
-- ----------------------------
DROP TABLE IF EXISTS `hwidcontrol`;
CREATE TABLE `hwidcontrol`  (
  `Hwid` varbinary(255) NOT NULL DEFAULT '',
  `HwidBan` int(11) NULL DEFAULT 0,
  `uID` varchar(50) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `uIP` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  PRIMARY KEY (`Hwid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for inuser
-- ----------------------------
DROP TABLE IF EXISTS `inuser`;
CREATE TABLE `inuser`  (
  `uid` varchar(30) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for jhevent
-- ----------------------------
DROP TABLE IF EXISTS `jhevent`;
CREATE TABLE `jhevent`  (
  `eventid` int(11) NULL DEFAULT 0,
  `subeventid` int(11) NULL DEFAULT 0,
  `itemid` varchar(5) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `itemname` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `itemnum` int(11) NULL DEFAULT 0,
  `itemclass` int(11) NULL DEFAULT 0,
  `IsMuti` int(11) NULL DEFAULT 0
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for jheventlog
-- ----------------------------
DROP TABLE IF EXISTS `jheventlog`;
CREATE TABLE `jheventlog`  (
  `uid` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `sendtime` datetime(0) NULL DEFAULT NULL,
  `eventid` int(11) NULL DEFAULT 0,
  `subeventid` int(11) NULL DEFAULT 0,
  `sendflag` int(11) NULL DEFAULT 0
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for jheventuser
-- ----------------------------
DROP TABLE IF EXISTS `jheventuser`;
CREATE TABLE `jheventuser`  (
  `uid` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `eventid` int(11) NULL DEFAULT 0,
  `sendflag` int(11) NULL DEFAULT 0
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for leveldistribution
-- ----------------------------
DROP TABLE IF EXISTS `leveldistribution`;
CREATE TABLE `leveldistribution`  (
  `LogDate` datetime(0) NULL DEFAULT NULL,
  `GroupType` smallint(6) NULL DEFAULT 0,
  `aLev` int(11) NULL DEFAULT NULL,
  `bLev` int(11) NULL DEFAULT NULL,
  `cLev` int(11) NULL DEFAULT NULL,
  `dLev` int(11) NULL DEFAULT NULL,
  `eLev` int(11) NULL DEFAULT NULL,
  `fLev` int(11) NULL DEFAULT NULL,
  `gLev` int(11) NULL DEFAULT NULL,
  `hLev` int(11) NULL DEFAULT NULL,
  `iLev` int(11) NULL DEFAULT NULL,
  `jLev` int(11) NULL DEFAULT NULL,
  `kLev` int(11) NULL DEFAULT NULL,
  `lLev` int(11) NULL DEFAULT NULL,
  `mLev` int(11) NULL DEFAULT NULL,
  `nLev` int(11) NULL DEFAULT NULL,
  `tCount` int(11) NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for leveldistribution_detail
-- ----------------------------
DROP TABLE IF EXISTS `leveldistribution_detail`;
CREATE TABLE `leveldistribution_detail`  (
  `LogDate` datetime(0) NULL DEFAULT NULL,
  `GroupType` smallint(6) NULL DEFAULT NULL,
  `[1]` int(11) NULL DEFAULT NULL,
  `[10]` int(11) NULL DEFAULT NULL,
  `[20]` int(11) NULL DEFAULT NULL,
  `[30]` int(11) NULL DEFAULT NULL,
  `[40]` int(11) NULL DEFAULT NULL,
  `[50]` int(11) NULL DEFAULT NULL,
  `[60]` int(11) NULL DEFAULT NULL,
  `[70]` int(11) NULL DEFAULT NULL,
  `[80]` int(11) NULL DEFAULT NULL,
  `[90]` int(11) NULL DEFAULT NULL,
  `[100]` int(11) NULL DEFAULT NULL,
  `[110]` int(11) NULL DEFAULT NULL,
  `[111]` int(11) NULL DEFAULT NULL,
  `[112]` int(11) NULL DEFAULT NULL,
  `[113]` int(11) NULL DEFAULT NULL,
  `[114]` int(11) NULL DEFAULT NULL,
  `[115]` int(11) NULL DEFAULT NULL,
  `[116]` int(11) NULL DEFAULT NULL,
  `[117]` int(11) NULL DEFAULT NULL,
  `[118]` int(11) NULL DEFAULT NULL,
  `[119]` int(11) NULL DEFAULT NULL,
  `[120]` int(11) NULL DEFAULT NULL,
  `[121]` int(11) NULL DEFAULT NULL,
  `[122]` int(11) NULL DEFAULT NULL,
  `[123]` int(11) NULL DEFAULT NULL,
  `[124]` int(11) NULL DEFAULT NULL,
  `[125]` int(11) NULL DEFAULT NULL,
  `[126]` int(11) NULL DEFAULT NULL,
  `[127]` int(11) NULL DEFAULT NULL,
  `[128]` int(11) NULL DEFAULT NULL,
  `[129]` int(11) NULL DEFAULT NULL,
  `[130]` int(11) NULL DEFAULT NULL,
  `[131]` int(11) NULL DEFAULT NULL,
  `[132]` int(11) NULL DEFAULT NULL,
  `[133]` int(11) NULL DEFAULT NULL,
  `[134]` int(11) NULL DEFAULT NULL,
  `[135]` int(11) NULL DEFAULT NULL,
  `[136]` int(11) NULL DEFAULT NULL,
  `[137]` int(11) NULL DEFAULT NULL,
  `[138]` int(11) NULL DEFAULT NULL,
  `[139]` int(11) NULL DEFAULT NULL,
  `[140]` int(11) NULL DEFAULT NULL,
  `[141]` int(11) NULL DEFAULT NULL,
  `[142]` int(11) NULL DEFAULT NULL,
  `[143]` int(11) NULL DEFAULT NULL,
  `[144]` int(11) NULL DEFAULT NULL,
  `[145]` int(11) NULL DEFAULT NULL,
  `tCount` int(11) NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for logininfo
-- ----------------------------
DROP TABLE IF EXISTS `logininfo`;
CREATE TABLE `logininfo`  (
  `uID` varchar(6) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `uPassword` varchar(8) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `uPermit` smallint(6) NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for loginuser
-- ----------------------------
DROP TABLE IF EXISTS `loginuser`;
CREATE TABLE `loginuser`  (
  `uID` varchar(12) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `aName` varchar(24) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `nowlevel` int(11) NULL DEFAULT NULL,
  `backlevel` int(11) NULL DEFAULT NULL,
  `gaplevel` int(11) NULL DEFAULT NULL,
  `nowexp` int(11) NULL DEFAULT NULL,
  `backexp` int(11) NULL DEFAULT NULL,
  `gapexp` int(11) NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for loginversioninfo
-- ----------------------------
DROP TABLE IF EXISTS `loginversioninfo`;
CREATE TABLE `loginversioninfo`  (
  `LoginVersion` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `LoginVersionSeq` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for masterinfo
-- ----------------------------
DROP TABLE IF EXISTS `masterinfo`;
CREATE TABLE `masterinfo`  (
  `uLogintime` datetime(0) NULL DEFAULT NULL,
  `aWorldNumber` tinyint(4) NULL DEFAULT NULL,
  `uID` varchar(12) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `uSaveMoney` int(11) NULL DEFAULT NULL,
  `uSaveItem` varchar(700) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `aName01` varchar(24) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `aName02` varchar(24) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `aName03` varchar(24) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `SeyisBar` int(11) NULL DEFAULT 0,
  `SaveSocket` varchar(800) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT ''
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for memberauth
-- ----------------------------
DROP TABLE IF EXISTS `memberauth`;
CREATE TABLE `memberauth`  (
  `uID` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `AuthType` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `FindFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `MoveFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `MoveZoneFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `CallFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `HideFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ShowFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `KickFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `BlockFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `MonCallFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `EquipFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `UnequipFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `YchatFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `NchatFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `NoticeFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ItemFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `MoneyFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ExpFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `DieFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `GodFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ChatFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `TradeFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ShopFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `PShopFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `GItemFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `DItemFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `AttackFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `UZonemoveFlag` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `DailyRewardTime` int(11) NULL DEFAULT 0,
  UNIQUE INDEX `uID`(`uID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = gb2312 COLLATE = gb2312_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for memberinfo
-- ----------------------------
DROP TABLE IF EXISTS `memberinfo`;
CREATE TABLE `memberinfo`  (
  `uUpdateTime` datetime(0) NULL DEFAULT NULL,
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `uLoginState` int(11) NULL DEFAULT 0,
  `uIP` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `uID` varchar(50) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `uPassword` varchar(30) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT '',
  `uCheckMOTP` int(11) NULL DEFAULT 0,
  `uMousePassword` varchar(4) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT '',
  `uSecretCard` int(11) NULL DEFAULT 0,
  `uBlockInfo` int(11) NULL DEFAULT 0,
  `uUserSort` int(11) NULL DEFAULT 0,
  `uGoodFellow` int(11) NULL DEFAULT 0,
  `uLoginPlace` int(11) NULL DEFAULT 0,
  `uLoginPremium` int(11) NULL DEFAULT 0,
  `uTraceState` int(11) NULL DEFAULT 0,
  `uBonus100Money` char(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT '0',
  `uPremiumServerExpirationDate` int(11) NULL DEFAULT 0,
  `uUseState` int(11) NULL DEFAULT 0,
  `uCash` int(11) NULL DEFAULT 0,
  `uBonusCash` int(11) NULL DEFAULT 0,
  `aWorldNumber` int(11) NULL DEFAULT 1,
  `Hwid` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT NULL,
  `uMail` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT NULL,
  `uPassword_temp` varchar(10) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT NULL,
  `nickname` varchar(25) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `uID`(`uID`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 17 CHARACTER SET = utf8 COLLATE = utf8_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for news
-- ----------------------------
DROP TABLE IF EXISTS `news`;
CREATE TABLE `news`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `Date` timestamp(0) NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `Title` varchar(5000) CHARACTER SET latin7 COLLATE latin7_bin NOT NULL,
  `ShortDesc` varchar(5000) CHARACTER SET latin7 COLLATE latin7_bin NOT NULL,
  `Image` varchar(5000) CHARACTER SET latin7 COLLATE latin7_bin NOT NULL,
  `HtmlCode` text CHARACTER SET latin7 COLLATE latin7_bin NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 37 CHARACTER SET = latin7 COLLATE = latin7_bin ROW_FORMAT = Compact;

-- ----------------------------
-- Table structure for oldrankinfo
-- ----------------------------
DROP TABLE IF EXISTS `oldrankinfo`;
CREATE TABLE `oldrankinfo`  (
  `RankInfoDragon` varbinary(1000) NULL DEFAULT '',
  `RankPointDragon` varbinary(100) NULL DEFAULT '',
  `RankInfoSnake` varbinary(1000) NULL DEFAULT '',
  `RankPointSnake` varbinary(100) NULL DEFAULT NULL,
  `RankInfoTiger` varbinary(1000) NULL DEFAULT '',
  `RankPointTiger` varbinary(100) NULL DEFAULT NULL,
  `RankInfoSky` varbinary(1000) NULL DEFAULT '',
  `RankPointSky` varbinary(100) NULL DEFAULT ''
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Table structure for paymentform
-- ----------------------------
DROP TABLE IF EXISTS `paymentform`;
CREATE TABLE `paymentform`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `uID` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `paymentReference` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `status` int(11) NULL DEFAULT 0,
  `totalprice` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `cash` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `pIP` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `pTime` datetime(0) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for pc_info
-- ----------------------------
DROP TABLE IF EXISTS `pc_info`;
CREATE TABLE `pc_info`  (
  `mPCIP` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for pcroomipinfo
-- ----------------------------
DROP TABLE IF EXISTS `pcroomipinfo`;
CREATE TABLE `pcroomipinfo`  (
  `uStartIP` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `uEndIP` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = gb2312 COLLATE = gb2312_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for playtimenewda
-- ----------------------------
DROP TABLE IF EXISTS `playtimenewda`;
CREATE TABLE `playtimenewda`  (
  `uid` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `aname` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `F3` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `F4` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `F5` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for playtimenewxiao
-- ----------------------------
DROP TABLE IF EXISTS `playtimenewxiao`;
CREATE TABLE `playtimenewxiao`  (
  `uid` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `aname` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `F3` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `F4` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `F5` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for rankinfo
-- ----------------------------
DROP TABLE IF EXISTS `rankinfo`;
CREATE TABLE `rankinfo`  (
  `uUpdateTime` datetime(0) NULL DEFAULT NULL,
  `aUpdateTime` datetime(0) NULL DEFAULT NULL,
  `uID` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `aWorldNumber` int(11) NULL DEFAULT NULL,
  `aName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `aTribe` int(11) NULL DEFAULT NULL,
  `aPreviousTribe` int(11) NULL DEFAULT NULL,
  `aLevel` int(11) NULL DEFAULT NULL,
  `aGeneralExperience` int(11) NULL DEFAULT NULL,
  `aGuildName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `aKillOtherTribe` int(11) NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for recommandinfo
-- ----------------------------
DROP TABLE IF EXISTS `recommandinfo`;
CREATE TABLE `recommandinfo`  (
  `Island` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `Partition` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `World` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = gb2312 COLLATE = gb2312_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for registereduser
-- ----------------------------
DROP TABLE IF EXISTS `registereduser`;
CREATE TABLE `registereduser`  (
  `userName` varchar(13) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `password` varchar(13) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `secret` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `email` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for replace_itemlist
-- ----------------------------
DROP TABLE IF EXISTS `replace_itemlist`;
CREATE TABLE `replace_itemlist`  (
  `zhengfai` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `xiefai` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mofai` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for replace_skillcode
-- ----------------------------
DROP TABLE IF EXISTS `replace_skillcode`;
CREATE TABLE `replace_skillcode`  (
  `zhengfai` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `xiefai` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mofai` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for replace_user
-- ----------------------------
DROP TABLE IF EXISTS `replace_user`;
CREATE TABLE `replace_user`  (
  `uID` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `aTribe` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `reaTribe` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for secretcardinfo
-- ----------------------------
DROP TABLE IF EXISTS `secretcardinfo`;
CREATE TABLE `secretcardinfo`  (
  `cNumber01` int(11) NULL DEFAULT NULL,
  `cNumber02` int(11) NULL DEFAULT NULL,
  `cNumber03` int(11) NULL DEFAULT NULL,
  `cNumber04` int(11) NULL DEFAULT NULL,
  `cNumber05` int(11) NULL DEFAULT NULL,
  `cNumber06` varchar(11) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `cNumber07` int(11) NULL DEFAULT NULL,
  `cNumber08` int(11) NULL DEFAULT NULL,
  `cNumber09` int(11) NULL DEFAULT NULL,
  `cNumber10` int(11) NULL DEFAULT NULL,
  `cNumber11` int(11) NULL DEFAULT NULL,
  `cNumber12` int(11) NULL DEFAULT NULL,
  `cNumber13` int(11) NULL DEFAULT NULL,
  `cNumber14` int(11) NULL DEFAULT NULL,
  `cNumber15` int(11) NULL DEFAULT NULL,
  `cNumber16` int(11) NULL DEFAULT NULL,
  `cNumber17` int(11) NULL DEFAULT NULL,
  `cNumber18` int(11) NULL DEFAULT NULL,
  `cNumber19` int(11) NULL DEFAULT NULL,
  `cNumber20` varchar(11) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `cNumber21` int(11) NULL DEFAULT NULL,
  `cNumber22` int(11) NULL DEFAULT NULL,
  `cNumber23` int(11) NULL DEFAULT NULL,
  `cNumber24` int(11) NULL DEFAULT NULL,
  `cNumber25` int(11) NULL DEFAULT NULL,
  `cNumber26` int(11) NULL DEFAULT NULL,
  `cNumber27` int(11) NULL DEFAULT NULL,
  `cNumber28` int(11) NULL DEFAULT NULL,
  `cNumber29` int(11) NULL DEFAULT NULL,
  `cNumber30` int(11) NULL DEFAULT NULL,
  `cNumber31` int(11) NULL DEFAULT NULL,
  `cNumber32` int(11) NULL DEFAULT NULL,
  `cNumber33` int(11) NULL DEFAULT NULL,
  `cNumber34` int(11) NULL DEFAULT NULL,
  `cNumber35` int(11) NULL DEFAULT NULL,
  `cNumber36` int(11) NULL DEFAULT NULL,
  `cNumber37` int(11) NULL DEFAULT NULL,
  `cNumber38` int(11) NULL DEFAULT NULL,
  `cNumber39` int(11) NULL DEFAULT NULL,
  `cNumber40` int(11) NULL DEFAULT NULL,
  `cNumber41` int(11) NULL DEFAULT NULL,
  `cNumber42` int(11) NULL DEFAULT NULL,
  `cNumber43` int(11) NULL DEFAULT NULL,
  `cNumber44` int(11) NULL DEFAULT NULL,
  `cNumber45` int(11) NULL DEFAULT NULL,
  `cNumber46` int(11) NULL DEFAULT NULL,
  `cNumber47` int(11) NULL DEFAULT NULL,
  `cNumber48` int(11) NULL DEFAULT NULL,
  `cNumber49` int(11) NULL DEFAULT NULL,
  `cNumber50` int(11) NULL DEFAULT NULL,
  `cID` int(11) NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = gb2312 COLLATE = gb2312_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for send_errorlog
-- ----------------------------
DROP TABLE IF EXISTS `send_errorlog`;
CREATE TABLE `send_errorlog`  (
  `InDate` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `uID` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `Msg` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for send_history
-- ----------------------------
DROP TABLE IF EXISTS `send_history`;
CREATE TABLE `send_history`  (
  `InDate` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `uID` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `beforeCode` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `beforeValue` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `inCode` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `inValue` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `inPosition` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for send_item
-- ----------------------------
DROP TABLE IF EXISTS `send_item`;
CREATE TABLE `send_item`  (
  `uID` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `iCode` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `iValue` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for send_itembackup
-- ----------------------------
DROP TABLE IF EXISTS `send_itembackup`;
CREATE TABLE `send_itembackup`  (
  `InDate` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `uID` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `MasterInfo_uSaveItem` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `MasterInfo_uSaveItemValue` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `MasterInfo_uSaveItem2` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `MasterInfo_uSaveItem2Value` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for status
-- ----------------------------
DROP TABLE IF EXISTS `status`;
CREATE TABLE `status`  (
  `state` int(11) NOT NULL
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_unicode_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Table structure for tempguild
-- ----------------------------
DROP TABLE IF EXISTS `tempguild`;
CREATE TABLE `tempguild`  (
  `uid` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `aname` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for temptbl
-- ----------------------------
DROP TABLE IF EXISTS `temptbl`;
CREATE TABLE `temptbl`  (
  `Col002` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `Col003` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for tribecontrol
-- ----------------------------
DROP TABLE IF EXISTS `tribecontrol`;
CREATE TABLE `tribecontrol`  (
  `aTribeType0Count` int(11) NULL DEFAULT 0,
  `aCreateFlag0` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `aTribeType1Count` int(11) NULL DEFAULT 0,
  `aCreateFlag1` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `aTribeType2Count` int(11) NULL DEFAULT 0,
  `aCreateFlag2` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `aWorldNumber` int(11) NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = gb2312 COLLATE = gb2312_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for tribeinfo
-- ----------------------------
DROP TABLE IF EXISTS `tribeinfo`;
CREATE TABLE `tribeinfo`  (
  `mTribeVoteInfo` text CHARACTER SET gb2312 COLLATE gb2312_bin NULL,
  `mTribe01Master` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `mTribe01SubMasterInfo` text CHARACTER SET gb2312 COLLATE gb2312_bin NULL,
  `mTribe02Master` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `mTribe02SubMasterInfo` text CHARACTER SET gb2312 COLLATE gb2312_bin NULL,
  `mTribe03Master` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `mTribe03SubMasterInfo` text CHARACTER SET gb2312 COLLATE gb2312_bin NULL,
  `mTribe04Master` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `mTribe04SubMasterInfo` text CHARACTER SET gb2312 COLLATE gb2312_bin NULL,
  `aWorldNumber` int(11) NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = gb2312 COLLATE = gb2312_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for ucount
-- ----------------------------
DROP TABLE IF EXISTS `ucount`;
CREATE TABLE `ucount`  (
  `num` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `uCount` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `wDate` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `wTime` varchar(0) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for valetshopinfo
-- ----------------------------
DROP TABLE IF EXISTS `valetshopinfo`;
CREATE TABLE `valetshopinfo`  (
  `ValetShopName` varchar(40) CHARACTER SET gb2312 COLLATE gb2312_bin NOT NULL DEFAULT '',
  `ValetShop00` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop01` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop02` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop03` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop04` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop10` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop11` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop12` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop13` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop14` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop20` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop21` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop22` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop23` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop24` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop30` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop31` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop32` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop33` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop34` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop40` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop41` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop42` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop43` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShop44` varchar(200) CHARACTER SET gb2312 COLLATE gb2312_bin NULL DEFAULT NULL,
  `ValetShopBar` int(11) NULL DEFAULT 0,
  `ValetShopMoney` int(11) NULL DEFAULT 0,
  PRIMARY KEY (`ValetShopName`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = gb2312 COLLATE = gb2312_bin ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for webmall
-- ----------------------------
DROP TABLE IF EXISTS `webmall`;
CREATE TABLE `webmall`  (
  `gGiftItem01` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `gGiftItem01Cnt` int(11) NULL DEFAULT 0,
  `gGiftItem02` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `gGiftItem02Cnt` int(11) NULL DEFAULT 0,
  `gGiftItem03` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `gGiftItem03Cnt` int(11) NULL DEFAULT 0,
  `gGiftItem04` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `gGiftItem04Cnt` int(11) NULL DEFAULT 0,
  `gGiftItem05` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `gGiftItem05Cnt` int(11) NULL DEFAULT 0,
  `gGiftItem06` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `gGiftItem06Cnt` int(11) NULL DEFAULT 0,
  `gGiftItem07` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `gGiftItem07Cnt` int(11) NULL DEFAULT 0,
  `gGiftItem08` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `gGiftItem08Cnt` int(11) NULL DEFAULT 0,
  `gGiftItem09` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `gGiftItem09Cnt` int(11) NULL DEFAULT 0,
  `gGiftItem10` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `gGiftItem10Cnt` int(11) NULL DEFAULT 0,
  `gGiftItemSetNumber` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for webmallitem
-- ----------------------------
DROP TABLE IF EXISTS `webmallitem`;
CREATE TABLE `webmallitem`  (
  `gGiftItemSetNumber` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `gPurchaseCnt` int(11) NULL DEFAULT 0,
  `gUsedCnt` int(11) NULL DEFAULT 0,
  `gUseID` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NULL DEFAULT NULL,
  `gWebMallSeq` int(11) NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for worldinfo
-- ----------------------------
DROP TABLE IF EXISTS `worldinfo`;
CREATE TABLE `worldinfo`  (
  `mZone38WinTribeDate` datetime(0) NULL DEFAULT NULL,
  `mZone38WinTribe` tinyint(4) NULL DEFAULT NULL,
  `mTribe1SymbolDate` datetime(0) NULL DEFAULT NULL,
  `mTribe1Symbol` tinyint(4) NULL DEFAULT NULL,
  `mTribe2SymbolDate` datetime(0) NULL DEFAULT NULL,
  `mTribe2Symbol` tinyint(4) NULL DEFAULT NULL,
  `mTribe3SymbolDate` datetime(0) NULL DEFAULT NULL,
  `mTribe3Symbol` tinyint(4) NULL DEFAULT NULL,
  `mMonsterSymbolDate` datetime(0) NULL DEFAULT NULL,
  `mMonsterSymbol` tinyint(4) NULL DEFAULT NULL,
  `mTribe1Point` int(11) NULL DEFAULT NULL,
  `mTribe2Point` int(11) NULL DEFAULT NULL,
  `mTribe3Point` int(11) NULL DEFAULT NULL,
  `mCloseTime` tinyint(4) NULL DEFAULT NULL,
  `mCloseTribe` tinyint(4) NULL DEFAULT NULL,
  `mFormationCount` varchar(96) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mGetStoneCount` bigint(20) NULL DEFAULT NULL,
  `mLostStoneCount` bigint(20) NULL DEFAULT NULL,
  `mYongpokCount` bigint(20) NULL DEFAULT NULL,
  `mTribe01Master` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mTribe01SubMaster` varchar(300) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mTribe02Master` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mTribe02SubMaster` varchar(300) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mTribe03Master` varchar(15) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mTribe03SubMaster` varchar(300) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `tNotice01` tinyint(4) NULL DEFAULT NULL,
  `tNotice02` tinyint(4) NULL DEFAULT NULL,
  `tNotice03` tinyint(4) NULL DEFAULT NULL,
  `mTribe4SymbolDate` datetime(0) NULL DEFAULT NULL,
  `mTribe4Symbol` tinyint(4) NULL DEFAULT NULL,
  `mTribe4Point` int(11) NULL DEFAULT NULL,
  `mPossibleAlliance01Date` varchar(19) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mPossibleAlliance01Info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mPossibleAlliance02Date` varchar(19) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mPossibleAlliance02Info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mPossibleAlliance03Date` varchar(19) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mPossibleAlliance03Info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mPossibleAlliance04Date` varchar(19) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mPossibleAlliance04Info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mAlliance0101` int(11) NULL DEFAULT NULL,
  `mAlliance0102` int(11) NULL DEFAULT NULL,
  `mAlliance0201` int(11) NULL DEFAULT NULL,
  `mAlliance0202` int(11) NULL DEFAULT NULL,
  `mTribe1VoteState` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mTribe2VoteState` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mTribe3VoteState` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mTribe4VoteState` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mClose1VoteState` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mClose2VoteState` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mClose3VoteState` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mClose4VoteState` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mTribe4QuestDate` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mTribe4QuestState` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mTribe4QuestName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `aWorldNumber` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mAlliance01Date` datetime(0) NULL DEFAULT NULL,
  `mAlliance02Date` datetime(0) NULL DEFAULT NULL,
  `mTribe1VoteDate` datetime(0) NULL DEFAULT NULL,
  `mTribe2VoteDate` datetime(0) NULL DEFAULT NULL,
  `mTribe3VoteDate` datetime(0) NULL DEFAULT NULL,
  `mTribe4VoteDate` datetime(0) NULL DEFAULT NULL,
  `mClose1VoteDate` datetime(0) NULL DEFAULT NULL,
  `mClose2VoteDate` datetime(0) NULL DEFAULT NULL,
  `mClose3VoteDate` datetime(0) NULL DEFAULT NULL,
  `mClose4VoteDate` datetime(0) NULL DEFAULT NULL,
  `mUpdateTime` datetime(0) NULL DEFAULT NULL,
  `mTribeVoteInfo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mTribe01SubMasterInfo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mTribe02SubMasterInfo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mTribe03SubMasterInfo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `mTribe04SubMasterInfo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
