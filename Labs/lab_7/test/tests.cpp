#include <gtest/gtest.h>
#include <stdexcept>
#include <memory>
#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include "npcFactory.h"
#include "fightVisitor.h"
#include "consoleObserver.h"
#include "fileObserver.h"


// Тесты NPC
TEST(NPCTests, CreateOrcTest) {
    Orc orc("Pudge", 50.0f, 40.0f);
    EXPECT_EQ(orc.getType(), "Orc");
    EXPECT_EQ(orc.getName(), "Pudge");
    EXPECT_EQ(orc.getX(), 50.0f);
    EXPECT_EQ(orc.getY(), 40.0f);
}

TEST(NPCTests, CreateSquirrelTest) {
    Squirrel squirrel("Belka", 25.0f, 30.0f);
    EXPECT_EQ(squirrel.getType(), "Squirrel");
    EXPECT_EQ(squirrel.getName(), "Belka");
    EXPECT_EQ(squirrel.getX(), 25.0f);
    EXPECT_EQ(squirrel.getY(), 30.0f);
}

TEST(NPCTests, CreateBearTest) {
    Bear bear("Mishka", 75.0f, 80.0f);
    EXPECT_EQ(bear.getType(), "Bear");
    EXPECT_EQ(bear.getName(), "Mishka");
    EXPECT_EQ(bear.getX(), 75.0f);
    EXPECT_EQ(bear.getY(), 80.0f);
}

// Тесты создания с NPCFactory
TEST(NPCFactoryTests, CreateOrcTest) {
    std::vector<std::shared_ptr<NPC>> npcs;
    auto orc = NPCFactory::createNPC("Orc", "PudgeF", 70.0f, 33.0f, npcs);
    EXPECT_EQ(orc->getType(), "Orc");
    EXPECT_EQ(orc->getName(), "PudgeF");
    EXPECT_EQ(orc->getX(), 70.0f);
    EXPECT_EQ(orc->getY(), 33.0f);
}

TEST(NPCFactoryTests, CreateBearTest) {
    std::vector<std::shared_ptr<NPC>> npcs;
    auto bear = NPCFactory::createNPC("Bear", "MishkaF", 21.0f, 4.5f, npcs);
    EXPECT_EQ(bear->getType(), "Bear");
    EXPECT_EQ(bear->getName(), "MishkaF");
    EXPECT_EQ(bear->getX(), 21.0f);
    EXPECT_EQ(bear->getY(), 4.5f);
}

TEST(NPCFactoryTests, CreateSquirrelTest) {
    std::vector<std::shared_ptr<NPC>> npcs;
    auto squirrel = NPCFactory::createNPC("Squirrel", "BelkaF", 13.6f, 27.3f, npcs);
    EXPECT_EQ(squirrel->getType(), "Squirrel");
    EXPECT_EQ(squirrel->getName(), "BelkaF");
    EXPECT_EQ(squirrel->getX(), 13.6f);
    EXPECT_EQ(squirrel->getY(), 27.3f);
}


// Тест загрузки NPC из файла
TEST(NPCFactoryTests, LoadFromFileTest) {
    
    std::string filename = "test_creator.txt";
    std::ofstream file(filename);
    file << "Orc FightPudge 23 32\n";
    file << "Bear PandaPo 57 75\n";
    file << "Squirrel TurboBelka 52 25\n";
    file.close();

    std::vector<std::shared_ptr<NPC>> npcs;
    try {
        npcs = NPCFactory::loadFromFile(filename, npcs);
    } catch (const std::exception& e) {
        FAIL() << "Ошибка при загрузке NPC из файла: " << e.what();
    }

    EXPECT_EQ(npcs.size(), 3);
    EXPECT_EQ(npcs[0]->getName(), "FightPudge");
    EXPECT_EQ(npcs[1]->getName(), "PandaPo");
    EXPECT_EQ(npcs[2]->getName(), "TurboBelka");
}

// Тесты выявления ошибок
TEST(NPCFactoryTests, CreateWithInvalidCoordinatesTest) {
    std::vector<std::shared_ptr<NPC>> npcs;
    EXPECT_THROW(NPCFactory::createNPC("Orc", "Pudg", 600.0f, 100.0f, npcs), std::out_of_range);
}

TEST(NPCFactoryTests, CreateWithDuplicateNameTest) {
    std::vector<std::shared_ptr<NPC>> npcs;
    auto npc1 = NPCFactory::createNPC("Orc", "Pudg", 100, 100, npcs);
    npcs.push_back(npc1);
    EXPECT_THROW(NPCFactory::createNPC("Bear", "Pudg", 150.0f, 150.0f, npcs), std::runtime_error);
}

TEST(NPCFactoryTest, CreateNPCWithDuplicateCoordinates) {
    std::vector<std::shared_ptr<NPC>> npcs;
    auto npc1 = NPCFactory::createNPC("Squirrel", "Squirrel1", 50, 50, npcs);
    npcs.push_back(npc1);
    EXPECT_THROW(NPCFactory::createNPC("Bear", "Bear1", 50, 50, npcs), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}