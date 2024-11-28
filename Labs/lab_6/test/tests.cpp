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
    Orc orc("Pudge", 100.0f, 140.0f);
    EXPECT_EQ(orc.getType(), "Orc");
    EXPECT_EQ(orc.getName(), "Pudge");
    EXPECT_EQ(orc.getX(), 100.0f);
    EXPECT_EQ(orc.getY(), 140.0f);
}

TEST(NPCTests, CreateSquirrelTest) {
    Squirrel squirrel("Belka", 50.0f, 30.0f);
    EXPECT_EQ(squirrel.getType(), "Squirrel");
    EXPECT_EQ(squirrel.getName(), "Belka");
    EXPECT_EQ(squirrel.getX(), 50.0f);
    EXPECT_EQ(squirrel.getY(), 30.0f);
}

TEST(NPCTests, CreateBearTest) {
    Bear bear("Mishka", 200.0f, 210.0f);
    EXPECT_EQ(bear.getType(), "Bear");
    EXPECT_EQ(bear.getName(), "Mishka");
    EXPECT_EQ(bear.getX(), 200.0f);
    EXPECT_EQ(bear.getY(), 210.0f);
}

// Тесты создания с NPCFactory
TEST(NPCFactoryTests, CreateOrcTest) {
    std::vector<std::shared_ptr<NPC>> npcs;
    auto orc = NPCFactory::createNPC("Orc", "PudgeF", 170.0f, 133.0f, npcs);
    EXPECT_EQ(orc->getType(), "Orc");
    EXPECT_EQ(orc->getName(), "PudgeF");
    EXPECT_EQ(orc->getX(), 170.0f);
    EXPECT_EQ(orc->getY(), 133.0f);
}

TEST(NPCFactoryTests, CreateBearTest) {
    std::vector<std::shared_ptr<NPC>> npcs;
    auto bear = NPCFactory::createNPC("Bear", "MishkaF", 221.0f, 4.5f, npcs);
    EXPECT_EQ(bear->getType(), "Bear");
    EXPECT_EQ(bear->getName(), "MishkaF");
    EXPECT_EQ(bear->getX(), 221.0f);
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

// Тест боевых сражений и их логирования
TEST(FightVisitorTests, FightScenarioTest) {
    std::vector<std::shared_ptr<NPC>> npcs;
    npcs.push_back(std::make_shared<Squirrel>("Belka1", 1, 2));
    npcs.push_back(std::make_shared<Squirrel>("Belka2", 3, 4));
    npcs.push_back(std::make_shared<Bear>("Bear1", 2, 3));
    npcs.push_back(std::make_shared<Orc>("Orc1", 4, 5));
    npcs.push_back(std::make_shared<Orc>("Orc2", 5, 6));

    FightVisitor fightVisitor{2.0f};

    std::shared_ptr<ConsoleObserver> consoleObserver = std::make_shared<ConsoleObserver>();
    std::shared_ptr<FileObserver> fileObserver = std::make_shared<FileObserver>("log.txt");

    fightVisitor.addObserver(consoleObserver);
    fightVisitor.addObserver(fileObserver);

    fightVisitor.fight(npcs);

    std::ifstream logFile("log.txt");
    std::string logLine;

    std::vector<std::string> expectedLogs = {
        "Belka1 (Squirrel) fights Bear1 (Bear) -> Bear1 won.",
        "Belka2 (Squirrel) fights Bear1 (Bear) -> Bear1 won.",
        "Orc1 (Orc) fights Orc2 (Orc) -> Both Orcs died."
    };

    for (const auto& expected : expectedLogs) {
        bool found = false;
        while (std::getline(logFile, logLine)) {
            if (logLine == expected) {
                found = true;
                break;
            }
        }
        EXPECT_TRUE(found) << "Log not found for: " << expected;
    }

    EXPECT_EQ(npcs.size(), 1); 
    EXPECT_EQ(npcs[0]->getName(), "Bear1");
}


// Тест загрузки NPC из файла
TEST(NPCFactoryTests, LoadFromFileTest) {
    
    std::string filename = "test_creator.txt";
    std::ofstream file(filename);
    file << "Orc FightPudge 123 132\n";
    file << "Bear PandaPo 157 175\n";
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
    auto npc1 = NPCFactory::createNPC("Squirrel", "Squirrel1", 150, 150, npcs);
    npcs.push_back(npc1);
    EXPECT_THROW(NPCFactory::createNPC("Bear", "Bear1", 150, 150, npcs), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}