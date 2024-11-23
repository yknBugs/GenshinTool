from datetime import datetime
from math import floor
import math
import random
# from symbol import testlist
import pygame
import os
from pygame.color import *

windowPosX = 100
windowPosY = 50

screenSizeX = 1280
screenSizeY = 720

pygame.init()
baseFont = pygame.font.SysFont("SimHei", 30)
smallFont = pygame.font.SysFont("SimHei", 20)

#创建窗口:
os.environ['SDL_VIDEO_WINDOW_POS'] = "%d,%d" % (windowPosX, windowPosY)
screen=pygame.display.set_mode((screenSizeX, screenSizeY), pygame.DOUBLEBUF, 32)
clock=pygame.time.Clock()
pygame.display.set_caption("好玩的")

gFPS = 60


#工具函数
class MyUtil:
    def __init__(self):
        pass

    def drawCDRect(self, colorOut, colorIn, posX, posY, size, CDNow, CDMax):
        CDNowSize = size * CDNow / CDMax
        CDOutRect = pygame.Rect(posX, posY, size, size)
        CDInRect = pygame.Rect(posX, posY, size, size - CDNowSize)
        pygame.draw.rect(screen, colorIn, CDOutRect)
        pygame.draw.rect(screen, colorOut, CDInRect)

    def drawHPRect(self, colorOut, colorIn, colorProgress, posX, posY, size, width, hpNow, hpMax, hpProgress, hpBuff):
        HPNowSize = (size - 4) * hpNow / hpMax
        HPProSize = (size - 4) * hpProgress / hpMax
        HPOutRect = pygame.Rect(posX, posY, size, width)
        HPInRect = pygame.Rect(posX + 2, posY + 2, HPNowSize, width - 4)
        HPProRect = pygame.Rect(posX + 2, posY + 2, HPProSize, width - 4)
        pygame.draw.rect(screen, colorOut, HPOutRect)
        if hpBuff is not None:
            HPBuffNowSize = size * hpBuff.buffValue / hpMax
            if HPBuffNowSize > size:
                HPBuffNowSize = size
            HPBuffInRect = pygame.Rect(posX, posY, HPBuffNowSize, width)
            pygame.draw.rect(screen, hpBuff.buffColor, HPBuffInRect)
        HPOutRect = pygame.Rect(posX + 2, posY + 2, size - 4, width - 4)
        pygame.draw.rect(screen, colorOut, HPOutRect)
        pygame.draw.rect(screen, colorProgress, HPProRect)
        pygame.draw.rect(screen, colorIn, HPInRect)

    def getDistance(self, aX, aY, bX, bY):
        return math.sqrt((aX-bX)*(aX-bX)+(aY-bY)*(aY-bY))

    def randBetween(self, min, max):
        return random.random() * (max - min) + min

#buff
class MyBuff:
    def __init__(self, buffid, buffName, buffMaxTime, buffCurrentTime, buffLevel, buffValue, buffColor):
        self.buffid = buffid
        self.buffName = buffName
        self.buffMaxTime = buffMaxTime
        self.buffCurrentTime = buffCurrentTime
        self.buffLevel = buffLevel
        self.buffValue = buffValue
        self.buffColor = buffColor

    def tick(self):
        if self.buffCurrentTime > 0:
            self.buffCurrentTime = self.buffCurrentTime - 1

    def setCurrentTime(self, currentTime):
        self.buffCurrentTime = currentTime
        if currentTime < 0:
            self.buffCurrentTime = 0
        elif currentTime > self.buffMaxTime:
            self.buffMaxTime = currentTime


#元素，顺序1~7火水风雷草冰岩，11燃，15激，16冻
class MyElement:
    def __init__(self, elementId, elementValue, isSheild):
        self.isSheild = isSheild
        if isSheild == False:
            self.elementId = elementId
            self.elementValue = elementValue * 0.8
            self.elementMax = self.elementValue
            self.reduceSpeed = elementValue / 400.0 + 7.0
            self.reduceSpeed = self.elementValue / self.reduceSpeed

            if self.elementId == 16:
                self.reduceSpeed = 400.0
        else:
            self.elementId = elementId
            self.elementValue = elementValue
            self.elementMax = self.elementValue
            self.reduceSpeed = 0.0

    def toNoShield(self):
        if self.isSheild == True:
            return MyElement(self.elementId, self.elementValue, False)
        else:
            return self


    def fill(self, elementValue):
        if self.isSheild == False:
            if self.elementValue <= 0:
                self.elementValue = elementValue * 0.8
                self.elementMax = self.elementValue
                self.reduceSpeed = elementValue / 400.0 + 7.0
                self.reduceSpeed = self.elementValue / self.reduceSpeed

                if self.elementId == 16:
                    self.reduceSpeed = 400.0
            elif elementValue * 0.8 > self.elementValue:
                self.elementValue = elementValue * 0.8
                self.elementMax = self.elementValue
        else:
            self.elementValue = elementValue
            self.elementMax = self.elementValue


    def getReactionName(reactionId):
        if reactionId == 102 or reactionId == 201:
            return "蒸发"
        elif reactionId == 106 or reactionId == 601:
            return "融化"
        elif reactionId == 301 or reactionId == 302 or reactionId == 304 or reactionId == 306:
            return "扩散"
        elif reactionId == 701 or reactionId == 702 or reactionId == 704 or reactionId == 706:
            return "结晶"
        elif reactionId == 206:
            return "冻结"
        elif reactionId == 716:
            return "碎冰"
        elif reactionId == 104:
            return "超载"
        elif reactionId == 406:
            return "超导"
        elif reactionId == 204:
            return "感电"
        elif reactionId == 105:
            return "燃烧"
        elif reactionId == 205:
            return "绽放"
        elif reactionId == 245:
            return "超绽放"
        elif reactionId == 215:
            return "烈绽放"
        elif reactionId == 405:
            return "原激化"
        elif reactionId == 415:
            return "超激化"
        elif reactionId == 515:
            return "蔓激化"
        else:
            return " "
        
    def getReactionColor(reactionId):
        if reactionId == 102 or reactionId == 201:
            return (0,167,255)
        elif reactionId == 106 or reactionId == 601:
            return (166,253,253)
        elif reactionId == 301:
            return (246,86,59)
        elif reactionId == 302:
            return (0,167,255)
        elif reactionId == 304:
            return (211,134,255)
        elif reactionId == 306:
            return (166,253,253)
        elif reactionId == 701 or reactionId == 702 or reactionId == 704 or reactionId == 706:
            return (226,173,46)
        elif reactionId == 206:
            return (143,207,220)
        elif reactionId == 716:
            return (255,255,255)
        elif reactionId == 104:
            return (255,102,64)
        elif reactionId == 406:
            return (153,229,236)
        elif reactionId == 204:
            return (211,134,255)
        elif reactionId == 105:
            return (246,86,59)
        elif reactionId == 205:
            return (48,190,48)
        elif reactionId == 245:
            return (153,232,41)
        elif reactionId == 215:
            return (255,102,64)
        elif reactionId == 405:
            return (153,232,41)
        elif reactionId == 415:
            return (211,134,255)
        elif reactionId == 515:
            return (48,190,48)
        else:
            return (255,255,255)

    def tick(self):
        if self.elementValue > 0:
            self.elementValue = self.elementValue - self.reduceSpeed / gFPS
        else:
            self.elementValue = 0.0
            self.elementMax = 0.0
            self.reduceSpeed = 0.0

        if self.elementId == 16:
            self.reduceSpeed = self.reduceSpeed + 100.0 / gFPS

    def getElementName(self):
        if self.elementId == 1:
            return "火"
        elif self.elementId == 2:
            return "水"
        elif self.elementId == 3:
            return "风"
        elif self.elementId == 4:
            return "雷"
        elif self.elementId == 5:
            return "草"
        elif self.elementId == 6:
            return "冰"
        elif self.elementId == 7:
            return "岩"
        elif self.elementId == 11:
            return "燃"
        elif self.elementId == 15:
            return "激"
        elif self.elementId == 16:
            return "冻"
        else:
            return " "

    def getElementColor(self):
        if self.elementId == 1:
            return (246,86,59)
        elif self.elementId == 2:
            return (0,167,255)
        elif self.elementId == 3:
            return (88,223,195)
        elif self.elementId == 4:
            return (211,134,255)
        elif self.elementId == 5:
            return (48,190,48)
        elif self.elementId == 6:
            return (166,253,253)
        elif self.elementId == 7:
            return (226,173,46)
        elif self.elementId == 11:
            return (255,102,64)
        elif self.elementId == 15:
            return (153,232,41)
        elif self.elementId == 16:
            return (143,207,220)
        else:
            return (255,255,255)

#实体类
class MyEntity:
    def __init__(self, HP, ATK, EM, posX, posY, teamId):
        self.buffList = []
        self.elementList = []
        self.elementCount = 0
        #元素反应相关
        self.burningCD = 0
        self.burningEM = 0
        self.eleChargeCD = 0
        self.eleChargeEM = 0
        #属性
        self.HP = HP
        self.maxHP = HP
        self.HPDecrease = HP
        self.ATK = ATK
        self.EM = EM
        self.posX = posX
        self.posY = posY
        self.teamId = teamId
        #待处理事件
        self.reactionList = []
        self.lastATKDMG = 0
        self.lastATKElement = MyElement(1,1000.0,False)
        self.lastEMDMGList = []
        self.lastEMDMGColor = []
        self.lastEMDMGSize = 0
        #技能CD
        self.skillCD = []
        self.skillmaxCD = []
        self.skillLimit = []
        self.skillCount = 0

    def damageOrHeal(self, HPChange):
        sheildBuff = None
        if HPChange < 0:
            HPChangeMulti = 100
            for i in self.buffList:
                if i.buffid == 761:
                    HPChangeMulti += i.buffValue
                if i.buffid == 2002:
                    HPChangeMulti -= i.buffValue
                if i.buffid == 700:
                    sheildBuff = i
            if HPChangeMulti < 0:
                HPChangeMulti = 0
            HPChange = HPChange * HPChangeMulti // 100

        if sheildBuff is not None and HPChange < 0:
            if sheildBuff.buffValue + HPChange > 0:
                sheildBuff.buffValue = sheildBuff.buffValue + HPChange
                HPChange = 0
            else:
                HPChange = HPChange + sheildBuff.buffValue
                sheildBuff.buffValue = 0
                sheildBuff.buffCurrentTime = 0

        self.HP += HPChange
        if self.HP < 0:
            self.HP = 0
        if self.HP > self.maxHP:
            self.HP = self.maxHP

    def hasElement(self, elementId):
        for i in range(self.elementCount):
            if self.elementList[i].elementId == elementId:
                return i
        return -1

    def reactionValue(self, listIndex, elementValue, scale):
        if self.elementList[listIndex].elementValue > elementValue * scale:
            self.elementList[listIndex].elementValue -= elementValue * scale
            return 0.0
        else:
            t = elementValue - self.elementList[listIndex].elementValue / scale
            self.elementList.pop(listIndex)
            self.elementCount = self.elementCount - 1
            return t

    def addBuff(self, buff):
        for i in range(len(self.buffList)):
            if self.buffList[i].buffid == buff.buffid:
                if self.buffList[i].buffLevel == buff.buffLevel and self.buffList[i].buffValue == buff.buffValue and self.buffList[i].buffCurrentTime < buff.buffCurrentTime:
                    self.buffList[i] = buff
                elif self.buffList[i].buffLevel == buff.buffLevel and self.buffList[i].buffValue < buff.buffValue:
                    self.buffList[i] = buff
                elif self.buffList[i].buffLevel < buff.buffLevel:
                    self.buffList[i] = buff
                return
        self.buffList.append(buff)

    def addElement(self, elementId, elementValue, ATK, EM):
        #非已有的元素，是否和已经有的发生反应
        reactionId = 0
        ATKSumDMG = ATK
        self.reactionList.clear()
        self.lastEMDMGList.clear()
        self.lastEMDMGColor.clear()
        self.lastEMDMGSize = 0
        #火系反应
        if elementId == 1:
            #火雷
            i = self.hasElement(4)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 1.0)
                if 104 not in self.reactionList:
                    self.reactionList.append(104)
                    self.lastEMDMGList.append(EM * 40)
                    self.lastEMDMGColor.append(MyElement.getReactionColor(104))
                    self.lastEMDMGSize = self.lastEMDMGSize + 1
                reactionId = 104
            #火冰
            i = self.hasElement(6)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 2.0)
                if 106 not in self.reactionList:
                    self.reactionList.append(106)
                    ATKSumDMG = ATKSumDMG * 2 + EM
                reactionId = 106
            #火冻
            i = self.hasElement(16)
            if i != -1 and elementValue > 0:
                self.reactionValue(i, elementValue, 2.0)
                elementValue = 0
                if 106 not in self.reactionList:
                    self.reactionList.append(106)
                    ATKSumDMG = ATKSumDMG * 2 + EM
                reactionId = 106
            #火水
            i = self.hasElement(2)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 0.5)
                if 102 not in self.reactionList:
                    self.reactionList.append(102)
                    ATKSumDMG = floor(ATKSumDMG * 3 / 2 + EM)
                reactionId = 102
            #火草和火激
            if (self.hasElement(5) != -1 or self.hasElement(15) != -1) and elementValue > 0:
                self.burningEM = EM
                if elementValue < 1000:
                    elementValue = 1000.0
                j = self.hasElement(1)
                if j == -1:
                    self.elementList.append(MyElement(1, elementValue, False))
                    self.elementCount = self.elementCount + 1
                else:
                    self.elementList[j].fill(elementValue)
                j = self.hasElement(11)
                if j == -1:
                    self.elementList.append(MyElement(11, 2000.0, True))
                    self.elementCount = self.elementCount + 1
                else:
                    self.elementList[j].elementValue = 2000.0
                elementValue = 0
                if 105 not in self.reactionList:
                    self.reactionList.append(105)
                reactionId = 105
        #水系反应
        if elementId == 2:
            #水燃
            i = self.hasElement(11)
            if i != -1 and elementValue > 0:
                elementReduce = elementValue
                elementValue = self.reactionValue(i, elementValue, 2)
                elementReduce = elementReduce - elementValue
                j = self.hasElement(1)
                if j != -1:
                    if self.elementList[j].elementValue > elementReduce * 2:
                        elementValue = elementValue + elementReduce
                    else:
                        elementValue = elementValue + self.elementList[j].elementValue * 0.5
                if 201 not in self.reactionList:
                    self.reactionList.append(201)
                    ATKSumDMG = ATKSumDMG * 2 + EM
                reactionId = 201
            #水火
            i = self.hasElement(1)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 2)
                if 201 not in self.reactionList:
                    self.reactionList.append(201)
                    ATKSumDMG = ATKSumDMG * 2 + EM
                reactionId = 201
            #水冰
            i = self.hasElement(6)
            if i != -1 and elementValue > 0:
                elementReduce = elementValue
                elementValue = self.reactionValue(i, elementValue, 1)
                elementReduce = elementReduce - elementValue
                j = self.hasElement(16)
                if j == -1:
                    self.elementList.append(MyElement(16, elementReduce * 2, False))
                    self.elementCount = self.elementCount + 1
                else:
                    self.elementList[j].fill(elementReduce * 2)
                if 206 not in self.reactionList:
                    self.reactionList.append(206)
                reactionId = 206
            #水草
            i = self.hasElement(5)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 0.5)
                if 205 not in self.reactionList:
                    self.reactionList.append(205)
                reactionId = 205
            #水激
            i = self.hasElement(15)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 0.5)
                if 205 not in self.reactionList:
                    self.reactionList.append(205)
                reactionId = 205
            #水雷
            i = self.hasElement(4)
            if i != -1 and elementValue > 0:
                self.eleChargeEM = EM
                if 204 not in self.reactionList:
                    self.reactionList.append(204)
                reactionId = 204
        #风系反应
        if elementId == 3:
            #风燃
            i = self.hasElement(11)
            if i != -1 and elementValue > 0:
                elementReduce = elementValue
                elementValue = self.reactionValue(i, elementValue, 0.5)
                elementReduce = elementReduce - elementValue
                j = self.hasElement(1)
                if j != -1:
                    if self.elementList[j].elementValue > elementReduce * 0.5:
                        elementValue = elementValue + elementReduce
                    else:
                        elementValue = elementValue + self.elementList[j].elementValue * 2
                if 301 not in self.reactionList:
                    self.reactionList.append(301)
                    self.lastEMDMGList.append(EM * 12)
                    self.lastEMDMGColor.append(MyElement.getReactionColor(301))
                    self.lastEMDMGSize = self.lastEMDMGSize + 1
                reactionId = 301
            #风火
            i = self.hasElement(1)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 0.5)
                if 301 not in self.reactionList:
                    self.reactionList.append(301)
                    self.lastEMDMGList.append(EM * 12)
                    self.lastEMDMGColor.append(MyElement.getReactionColor(301))
                    self.lastEMDMGSize = self.lastEMDMGSize + 1
                reactionId = 301
            #风雷
            i = self.hasElement(4)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 0.5)
                if 304 not in self.reactionList:
                    self.reactionList.append(304)
                    self.lastEMDMGList.append(EM * 12)
                    self.lastEMDMGColor.append(MyElement.getReactionColor(304))
                    self.lastEMDMGSize = self.lastEMDMGSize + 1
                reactionId = 304
            #风水
            i = self.hasElement(2)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 0.5)
                if 302 not in self.reactionList:
                    self.reactionList.append(302)
                    self.lastEMDMGList.append(EM * 12)
                    self.lastEMDMGColor.append(MyElement.getReactionColor(302))
                    self.lastEMDMGSize = self.lastEMDMGSize + 1
                reactionId = 302
            #风冰
            i = self.hasElement(6)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 0.5)
                if 306 not in self.reactionList:
                    self.reactionList.append(306)
                    self.lastEMDMGList.append(EM * 12)
                    self.lastEMDMGColor.append(MyElement.getReactionColor(306))
                    self.lastEMDMGSize = self.lastEMDMGSize + 1
                reactionId = 306
            #风冻
            i = self.hasElement(16)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 0.5)
                if 306 not in self.reactionList:
                    self.reactionList.append(306)
                    self.lastEMDMGList.append(EM * 12)
                    self.lastEMDMGColor.append(MyElement.getReactionColor(306))
                    self.lastEMDMGSize = self.lastEMDMGSize + 1
                reactionId = 306
        #雷系反应
        if elementId == 4:
            #雷冰
            i = self.hasElement(6)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 1.0)
                if 406 not in self.reactionList:
                    self.reactionList.append(406)
                    self.lastEMDMGList.append(EM * 10)
                    self.lastEMDMGColor.append(MyElement.getReactionColor(406))
                    self.lastEMDMGSize = self.lastEMDMGSize + 1
                reactionId = 406
            #雷冻
            i = self.hasElement(16)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 1.0)
                elementValue = 0
                if 406 not in self.reactionList:
                    self.reactionList.append(406)
                    self.lastEMDMGList.append(EM * 10)
                    self.lastEMDMGColor.append(MyElement.getReactionColor(406))
                    self.lastEMDMGSize = self.lastEMDMGSize + 1
                reactionId = 406
            #雷激
            i = self.hasElement(15)
            if i != -1 and elementValue > 0:
                if 415 not in self.reactionList:
                    self.reactionList.append(415)
                    ATKSumDMG = ATKSumDMG + EM * 11
                reactionId = 415
            #雷草
            i = self.hasElement(5)
            if i != -1 and elementValue > 0:
                elementReduce = elementValue
                elementValue = self.reactionValue(i, elementValue, 1)
                elementReduce = elementReduce - elementValue
                j = self.hasElement(15)
                if j == -1:
                    self.elementList.append(MyElement(15, elementReduce, False))
                    self.elementCount = self.elementCount + 1
                else:
                    self.elementList[j].fill(elementReduce)
                if 405 not in self.reactionList:
                    self.reactionList.append(405)
                reactionId = 405
            #雷燃
            i = self.hasElement(11)
            if i != -1 and elementValue > 0:
                elementReduce = elementValue
                elementValue = self.reactionValue(i, elementValue, 1)
                elementReduce = elementReduce - elementValue
                j = self.hasElement(1)
                if j != -1:
                    if self.elementList[j].elementValue > elementReduce:
                        elementValue = elementValue + elementReduce
                    else:
                        elementValue = elementValue + self.elementList[j].elementValue
                if 104 not in self.reactionList:
                    self.reactionList.append(104)
                    self.lastEMDMGList.append(EM * 40)
                    self.lastEMDMGColor.append(MyElement.getReactionColor(104))
                    self.lastEMDMGSize = self.lastEMDMGSize + 1
                reactionId = 104
            #雷火
            i = self.hasElement(1)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 1)
                if 104 not in self.reactionList:
                    self.reactionList.append(104)
                    self.lastEMDMGList.append(EM * 40)
                    self.lastEMDMGColor.append(MyElement.getReactionColor(104))
                    self.lastEMDMGSize = self.lastEMDMGSize + 1
                reactionId = 104
            #雷水
            i = self.hasElement(2)
            if i != -1 and elementValue > 0:
                self.eleChargeEM = EM
                if 204 not in self.reactionList:
                    self.reactionList.append(204)
                reactionId = 204
        #草系反应
        if elementId == 5:
            #草激
            i = self.hasElement(15)
            if i != -1 and elementValue > 0:
                if 515 not in self.reactionList:
                    self.reactionList.append(515)
                    ATKSumDMG = ATKSumDMG + EM * 12
                reactionId = 515
            #草水
            i = self.hasElement(2)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 2)
                if 205 not in self.reactionList:
                    self.reactionList.append(205)
                reactionId = 205
            #草火
            i = self.hasElement(1)
            if i != -1 and elementValue > 0:
                self.elementList[i].fill(1000.0)
                self.burningEM = EM
                j = self.hasElement(5)
                if j == -1:
                    self.elementList.append(MyElement(5, elementValue, False))
                    self.elementCount = self.elementCount + 1
                else:
                    self.elementList[j].fill(elementValue)
                j = self.hasElement(11)
                if j == -1:
                    self.elementList.append(MyElement(11, 2000.0, True))
                    self.elementCount = self.elementCount + 1
                else:
                    self.elementList[j].elementValue = 2000.0
                elementValue = 0
                if 105 not in self.reactionList:
                    self.reactionList.append(105)
                reactionId = 105
            #草雷
            i = self.hasElement(4)
            if i != -1 and elementValue > 0:
                elementReduce = elementValue
                elementValue = self.reactionValue(i, elementValue, 1)
                elementReduce = elementReduce - elementValue
                j = self.hasElement(15)
                if j == -1:
                    self.elementList.append(MyElement(15, elementReduce, False))
                    self.elementCount = self.elementCount + 1
                else:
                    self.elementList[j].fill(elementReduce)
                if 405 not in self.reactionList:
                    self.reactionList.append(405)
                reactionId = 405
        #冰系反应
        if elementId == 6:
            #冰燃
            i = self.hasElement(11)
            if i != -1 and elementValue > 0:
                elementReduce = elementValue
                elementValue = self.reactionValue(i, elementValue, 0.5)
                elementReduce = elementReduce - elementValue
                j = self.hasElement(1)
                if j != -1:
                    if self.elementList[j].elementValue > elementReduce * 0.5:
                        elementValue = elementValue + elementReduce
                    else:
                        elementValue = elementValue + self.elementList[j].elementValue * 2
                if 601 not in self.reactionList:
                    self.reactionList.append(601)
                    ATKSumDMG = floor(ATKSumDMG * 3 / 2 + EM)
                reactionId = 601
            #冰火
            i = self.hasElement(1)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 0.5)
                if 601 not in self.reactionList:
                    self.reactionList.append(601)
                    ATKSumDMG = floor(ATKSumDMG * 3 / 2 + EM)
                reactionId = 601
            #冰雷
            i = self.hasElement(4)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 1.0)
                if 406 not in self.reactionList:
                    self.reactionList.append(406)
                    self.lastEMDMGList.append(EM * 10)
                    self.lastEMDMGColor.append(MyElement.getReactionColor(406))
                    self.lastEMDMGSize = self.lastEMDMGSize + 1
                reactionId = 406
            #冰水
            i = self.hasElement(2)
            if i != -1 and elementValue > 0:
                elementReduce = elementValue
                elementValue = self.reactionValue(i, elementValue, 1)
                elementReduce = elementReduce - elementValue
                j = self.hasElement(16)
                if j == -1:
                    self.elementList.append(MyElement(16, elementReduce * 2, False))
                    self.elementCount = self.elementCount + 1
                else:
                    self.elementList[j].fill(elementReduce * 2)
                if 206 not in self.reactionList:
                    self.reactionList.append(206)
                reactionId = 206
        #岩系反应
        if elementId == 7:
            #岩冻
            i = self.hasElement(16)
            if i != -1 and elementValue > 0:
                self.elementList[i].elementValue = 0.0
                if 716 not in self.reactionList:
                    self.reactionList.append(716)
                    self.lastEMDMGList.append(EM * 30)
                    self.lastEMDMGColor.append(MyElement.getReactionColor(716))
                    self.lastEMDMGSize = self.lastEMDMGSize + 1
                reactionId = 716
            #岩燃
            i = self.hasElement(11)
            if i != -1 and elementValue > 0:
                elementReduce = elementValue
                elementValue = self.reactionValue(i, elementValue, 0.5)
                elementReduce = elementReduce - elementValue
                j = self.hasElement(1)
                if j != -1:
                    if self.elementList[j].elementValue > elementReduce * 0.5:
                        elementValue = elementValue + elementReduce
                    else:
                        elementValue = elementValue + self.elementList[j].elementValue * 2
                if 701 not in self.reactionList:
                    self.reactionList.append(701)
                reactionId = 701
            #岩火
            i = self.hasElement(1)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 0.5)
                if 701 not in self.reactionList:
                    self.reactionList.append(701)
                reactionId = 701
            #岩雷
            i = self.hasElement(4)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 0.5)
                if 704 not in self.reactionList:
                    self.reactionList.append(704)
                reactionId = 704
            #岩水
            i = self.hasElement(2)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 0.5)
                if 702 not in self.reactionList:
                    self.reactionList.append(702)
                reactionId = 702
            #岩冰
            i = self.hasElement(6)
            if i != -1 and elementValue > 0:
                elementValue = self.reactionValue(i, elementValue, 0.5)
                if 706 not in self.reactionList:
                    self.reactionList.append(706)
                reactionId = 706
        
        if reactionId == 0 or reactionId == 204 or reactionId == 415 or reactionId == 515:
            #不反应或感电反应或激化反应，元素直接补充
            i = self.hasElement(elementId)
            if i != -1:
                self.elementList[i].fill(elementValue)
            elif elementValue > 0 and elementId != 3 and elementId != 7:
                #不发生反应，且元素不为风岩,直接共存
                self.elementList.append(MyElement(elementId, elementValue, False))
                self.elementCount = self.elementCount + 1

        #伤害结算
        self.lastATKDMG = ATKSumDMG
        self.lastATKElement = MyElement(elementId, elementValue, False)
        self.damageOrHeal(-ATKSumDMG)
        for i in range(self.lastEMDMGSize):
            self.damageOrHeal(-self.lastEMDMGList[i])
        
        return reactionId
    
    def tick(self, showList, showCD, showColor, showPosX, showPosY):
        #buff结算
        for i in range(len(self.buffList)):
            if self.buffList[i].buffid == 1001:
                if self.buffList[i].buffCurrentTime % gFPS == 1:
                    self.damageOrHeal(self.buffList[i].buffValue)
                    self.addElement(3,4000.0,10,1)
                    showList.append("+"+str(self.buffList[i].buffValue))
                    showColor.append((169,232,42))
                    showCD.append(gFPS * 3)
                    showPosX.append(self.posX - 80)
                    showPosY.append(self.posY + 10)
            if self.buffList[i].buffid == 2001:
                if self.buffList[i].buffCurrentTime % (gFPS//2) == 1:
                    self.damageOrHeal(self.buffList[i].buffValue)
                    showList.append("+"+str(self.buffList[i].buffValue))
                    showColor.append((169,232,42))
                    showCD.append(gFPS * 3)
                    showPosX.append(self.posX - 80)
                    showPosY.append(self.posY + 10)

            self.buffList[i].tick()
            if self.buffList[i].buffCurrentTime <= 0:
                self.buffList.pop(i)
                break
        #元素结算
        for i in range(self.elementCount):
            self.elementList[i].tick()
            if self.elementList[i].elementValue <= 0:
                self.elementList.pop(i)
                self.elementCount = self.elementCount - 1
                break
        #燃烧结算
        if self.burningCD > 0:
            self.burningCD = self.burningCD - 1
        i = self.hasElement(11)
        j = self.hasElement(5)
        h = self.hasElement(15)
        if j == -1 and h == -1 and i != -1:
            self.elementList.pop(i)
            self.elementCount = self.elementCount - 1
        if self.burningCD <= 0 and i != -1 and (j != -1 or h != -1):
            self.burningCD = gFPS / 4
            self.lastEMDMGList = [self.burningEM * 5]
            self.lastEMDMGColor = [MyElement.getReactionColor(105)]
            self.lastEMDMGSize = 1
            self.damageOrHeal(-self.burningEM * 5)
            if j != -1:
                self.elementList[j].elementValue -= 100.0
            if h != -1:
                self.elementList[h].elementValue -= 100.0
            if self.elementList[j].elementValue < 0:
                self.elementList[j].elementValue = 0.0
            if self.elementList[h].elementValue < 0:
                self.elementList[h].elementValue = 0.0
        #感电结算
        if self.eleChargeCD > 0:
            self.eleChargeCD = self.eleChargeCD - 1
        i = self.hasElement(2)
        j = self.hasElement(4)
        if i != -1 and j != -1 and self.eleChargeCD <= 0:
            self.eleChargeCD = gFPS
            self.lastEMDMGList = [self.eleChargeEM * 24]
            self.lastEMDMGColor = [MyElement.getReactionColor(204)]
            self.lastEMDMGSize = 1
            self.damageOrHeal(-self.eleChargeEM * 24)
            self.elementList[i].elementValue -= 400.0
            if self.elementList[i].elementValue < 0:
                self.elementList[i].elementValue = 0.0
            self.elementList[j].elementValue -= 400.0
            if self.elementList[j].elementValue < 0:
                self.elementList[j].elementValue = 0.0
        #技能CD
        for i in range(self.skillCount):
            if self.skillCD[i] > 0:
                self.skillCD[i] = self.skillCD[i] - 1

        #动态血条
        if self.HP > self.HPDecrease:
            self.HPDecrease = self.HP
        if self.HP < self.HPDecrease:
            self.HPDecrease = self.HPDecrease - floor(self.maxHP / 10 / gFPS)

    def showDamageText(self, showList, showCD, showColor, showPosX, showPosY):
        temp = -40
        HPChangeMulti = 100
        for i in self.buffList:
            if i.buffid == 761:
                HPChangeMulti += i.buffValue
            if i.buffid == 2002:
                HPChangeMulti -= i.buffValue
        if HPChangeMulti < 0:
            HPChangeMulti = 0

        for i in self.reactionList:
            showList.append(MyElement.getReactionName(i))
            showColor.append(MyElement.getReactionColor(i))
            showCD.append(gFPS * 3)
            showPosX.append(self.posX + 20)
            showPosY.append(self.posY + temp)
            temp = temp + 40
        self.reactionList.clear()
        if self.lastATKDMG > 0:
            showList.append(str(self.lastATKDMG * HPChangeMulti // 100))
            showColor.append(self.lastATKElement.getElementColor())
            showCD.append(gFPS * 3)
            showPosX.append(self.posX + 20)
            showPosY.append(self.posY + temp)
            self.reactionList.clear()
            temp = temp + 40
            self.lastATKDMG = 0
        if self.lastEMDMGSize > 0:
            temp = -40
            for i in range(self.lastEMDMGSize):
                showList.append(str(self.lastEMDMGList[i] * HPChangeMulti // 100))
                showColor.append(self.lastEMDMGColor[i])
                showCD.append(gFPS * 3)
                showPosX.append(self.posX - 50)
                showPosY.append(self.posY + temp)
            self.lastEMDMGList.clear()
            self.lastEMDMGColor.clear()
            self.lastEMDMGSize = 0

class MyState:
    def __init__(self):
        self.w = False
        self.a = False
        self.s = False
        self.d = False

#喷发
class MyBurst:
    def __init__(self, elementId, elementValue, size, posX, posY, ATK, EM, cd):
        self.elementId = elementId
        self.elementValue = elementValue
        self.size = size
        self.posX = posX
        self.posY = posY
        self.ATK = ATK
        self.EM = EM
        self.cd = cd
        self.cdMax = cd

    def show(self):
        selfElement = MyElement(self.elementId, self.elementValue, True)
        cdSize = self.size * self.cd / self.cdMax
        pygame.draw.circle(screen, selfElement.getElementColor(), (self.posX, self.posY), self.size)
        pygame.draw.circle(screen, (127, 127, 127), (self.posX, self.posY), cdSize)

    def tick(self):
        if self.cd > 0:
            self.cd = self.cd - 1

#草原核
class MySeed():
    def __init__(self, posX, posY, EM):
        self.posX = posX
        self.posY = posY
        self.EM = EM
        self.cd = 6 * gFPS
        self.reactionId = 205

    def tick(self):
        if self.cd > 0:
            self.cd = self.cd - 1

    def addElement(self, elementId, EM):
        #烈绽放
        if elementId == 1:
            self.cd = 0
            self.EM = EM
            self.reactionId = 215
        #超绽放
        if elementId == 4:
            self.cd = 0
            self.EM = EM
            self.reactionId = 245

    def show(self):
        pygame.draw.circle(screen, MyElement.getReactionColor(205), (self.posX, self.posY), 8)

    def showText(self, showList, showCD, showColor, showPosX, showPosY):
        showList.append(MyElement.getReactionName(self.reactionId))
        showColor.append(MyElement.getReactionColor(self.reactionId))
        showCD.append(gFPS * 3)
        showPosX.append(self.posX + 20)
        showPosY.append(self.posY - 40)
        return 1

#结晶
class MyCrystal():
    def __init__(self, posX, posY, EM):
        self.posX = posX
        self.posY = posY
        self.EM = EM
        self.cd = 1 * gFPS
        self.duration = 12 * gFPS
        self.color = (122, 78, 21)

    def show(self):
        pygame.draw.circle(screen, self.color, (self.posX, self.posY), 8)

    def tick(self):
        if self.cd > 0:
            self.cd = self.cd - 1
        if self.duration > 0:
            self.duration = self.duration - 1

#主程序
playTime = 0
myState = MyState()
myUtil = MyUtil()

player = MyEntity(10000, 100, 10, screenSizeX/2, screenSizeY/2, 0)
player.skillCD = [0, 0]
player.skillmaxCD = [8*gFPS, 15*gFPS]
player.skillLimit = [0, 40]
player.skillCount = 2

timeSinceLastDeath = 0
difficulty = 60*gFPS
lockDifficulty = True
mySeedList = []
myCrystalList = []
burstList = []
textList = []
textListCD = []
textListColor = []
textListPosX = []
textListPosY = []
showInfo = False
mspt = 0
tickStartTime = datetime.now()
tickEndTime = datetime.now()
tickFPSTime = datetime.now()
actualFPS = 0
lastActualFPS = 0
deathCount = 0
isGameOver = False
isPaused = False
isReallyPaused = False
while True:
    tickStartTime = datetime.now()
    if isGameOver == True:
        pygame.display.update()
        clock.tick(gFPS)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    isGameOver = False
                    player.damageOrHeal(64)
                    textList.append("+64")
                    textListColor.append((169,232,42))
                    textListCD.append(gFPS * 3)
                    textListPosX.append(player.posX - 80)
                    textListPosY.append(player.posY + 10)
                    player.buffList.clear()
                    player.addBuff(MyBuff(700, "盾", 5*gFPS, 5*gFPS, 100, player.maxHP//4, (255,127,39)))
                    player.addBuff(MyBuff(2001, "春", 10*gFPS, 10*gFPS, 1, 256, (255,127,39)))
                    player.addBuff(MyBuff(2002, "抗", 15*gFPS, 15*gFPS, 1, 90, (136,0,21)))
                    textList.append("复活")
                    textListColor.append((0,0,255))
                    textListCD.append(gFPS * 3)
                    textListPosX.append(screenSizeX / 2 - 20)
                    textListPosY.append(100)
                    timeSinceLastDeath = 0
                    myState.w = False
                    myState.a = False
                    myState.s = False
                    myState.d = False
        continue
    if isReallyPaused == True:
        pygame.display.update()
        clock.tick(gFPS)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    isPaused = False
                    isReallyPaused = False
                    textList.append("继续")
                    textListColor.append((0,255,0))
                    textListCD.append(gFPS * 3)
                    textListPosX.append(screenSizeX / 2 - 20)
                    textListPosY.append(150)
                    myState.w = False
                    myState.a = False
                    myState.s = False
                    myState.d = False
        continue
    if isPaused == True:
        isReallyPaused = True
    if player.HP <= 0:
        isGameOver = True
        deathCount = deathCount + 1
        textList.append("你死了")
        textListColor.append((255,0,0))
        textListCD.append(gFPS * 3)
        textListPosX.append(screenSizeX / 2 - 30)
        textListPosY.append(150)
        
    screen.fill((0,0,0))

    #控制玩家移动
    speed_multi = 100
    for i in player.buffList:
        if i.buffid == 1011:
            speed_multi = speed_multi + i.buffValue
    if player.hasElement(16) == -1:
        if myState.a == True:
            player.posX -= (240 * speed_multi) // (100 * gFPS)
        if myState.d == True:
            player.posX += (240 * speed_multi) // (100 * gFPS)
        if myState.w == True:
            player.posY -= (240 * speed_multi) // (100 * gFPS)
        if myState.s == True:
            player.posY += (240 * speed_multi) // (100 * gFPS)

    #防止跑到边界外
    if player.posX < 110:
        player.posX = 110
    if player.posX > screenSizeX - 10:
        player.posX = screenSizeX - 10
    if player.posY < 10:
        player.posY = 10
    if player.posY > screenSizeY - 10:
        player.posY = screenSizeY - 10

    #随机生成喷发
    temp = myUtil.randBetween(0, 6*gFPS*gFPS)
    if temp < difficulty:
        randElementId = floor(myUtil.randBetween(1,8))
        randElementValue = 1000.0 * floor(myUtil.randBetween(1,5))
        randSize = floor(myUtil.randBetween(100,300))
        randPosX = floor(myUtil.randBetween(-190,screenSizeX+290))
        randPosY = floor(myUtil.randBetween(-290,screenSizeY+290))
        randATK = floor(myUtil.randBetween(100,800))
        randEM = floor(myUtil.randBetween(25,100))
        randCD = floor(myUtil.randBetween(1,4) * gFPS)
        burstList.append(MyBurst(randElementId,randElementValue,randSize,randPosX,randPosY,randATK,randEM,randCD))
    #爆发的帧事件
    burstList.sort(key=lambda x: x.cd, reverse=True)
    for i in range(len(burstList)):
        burstList[i].tick()
        if burstList[i].cd <= 0:
            #爆发
            if myUtil.getDistance(player.posX, player.posY, burstList[i].posX, burstList[i].posY) < burstList[i].size:
                player.addElement(burstList[i].elementId, burstList[i].elementValue,burstList[i].ATK,burstList[i].EM)
                for j in player.reactionList:
                    #绽放
                    if j == 205:
                        mySeedList.append(MySeed(player.posX, player.posY, burstList[i].EM))
                    #结晶
                    if j == 701 or j == 702 or j == 704 or j == 706:
                        myCrystalList.append(MyCrystal(player.posX, player.posY, burstList[i].EM))
                    #超导
                    if j == 406:
                        player.addBuff(MyBuff(761, "弱", 8*gFPS, 8*gFPS, burstList[i].EM, 40, (0,162,232)))
            #爆发对草种子
            for j in range(len(mySeedList)):
                if myUtil.getDistance(mySeedList[j].posX, mySeedList[j].posY, burstList[i].posX, burstList[i].posY) < burstList[i].size:
                    mySeedList[j].addElement(burstList[i].elementId, burstList[i].EM)
            burstList.pop(i)
            break
    for i in range(len(burstList)):
        burstList[i].show()

    #草种子帧事件
    for i in range(len(mySeedList)):
        mySeedList[i].tick()
        if mySeedList[i].cd <= 0:
            playerDistance = myUtil.getDistance(mySeedList[i].posX, mySeedList[i].posY, player.posX, player.posY)
            mySeedList[i].showText(textList, textListCD, textListColor, textListPosX, textListPosY)
            if mySeedList[i].reactionId == 205:
                if playerDistance < 100:
                    player.lastEMDMGList.append(mySeedList[i].EM * 40)
                    player.lastEMDMGColor.append(MyElement.getReactionColor(205))
                    player.lastEMDMGSize = player.lastEMDMGSize + 1
                    player.damageOrHeal(-mySeedList[i].EM * 40)
            if mySeedList[i].reactionId == 215:
                if playerDistance < 100:
                    player.lastEMDMGList.append(mySeedList[i].EM * 60)
                    player.lastEMDMGColor.append(MyElement.getReactionColor(215))
                    player.lastEMDMGSize = player.lastEMDMGSize + 1
                    player.damageOrHeal(-mySeedList[i].EM * 60)
            if mySeedList[i].reactionId == 245:
                if playerDistance < 1000:
                    player.lastEMDMGList.append(mySeedList[i].EM * 60)
                    player.lastEMDMGColor.append(MyElement.getReactionColor(245))
                    player.lastEMDMGSize = player.lastEMDMGSize + 1
                    player.damageOrHeal(-mySeedList[i].EM * 60)
            mySeedList.pop(i)
            break    
    for i in range(len(mySeedList)):
        mySeedList[i].show()

    #结晶帧事件
    for i in range(len(myCrystalList)):
        myCrystalList[i].tick()
        if myCrystalList[i].cd <= 0:
            playerDistance = myUtil.getDistance(myCrystalList[i].posX, myCrystalList[i].posY, player.posX, player.posY)
            if playerDistance < 20:
                player.addBuff(MyBuff(700, "盾", 15*gFPS, 15*gFPS, myCrystalList[i].EM, myCrystalList[i].EM*30, myCrystalList[i].color))
                myCrystalList[i].duration = 0
        if myCrystalList[i].duration <= 0:
            myCrystalList.pop(i)
            break
    for i in range(len(myCrystalList)):
        myCrystalList[i].show()

    #渲染反应伤害文字
    player.showDamageText(textList, textListCD, textListColor, textListPosX, textListPosY)

    #文字cd计算
    for i in range(len(textList)):
        textListCD[i] = textListCD[i] - 1
        if textListCD[i] <= 0:
            textList.pop(i)
            textListColor.pop(i)
            textListCD.pop(i)
            textListPosX.pop(i)
            textListPosY.pop(i)
            break
    
    #渲染受保护的GUI
    pygame.draw.rect(screen, (0,0,0), pygame.Rect(0,0,100,screenSizeY))
    pygame.draw.rect(screen, (255,255,255), pygame.Rect(100,0,2,screenSizeY))

    #渲染玩家位置
    pygame.draw.circle(screen, (255, 255, 255), (player.posX, player.posY), 16)
    #渲染玩家血量
    sheidBuff = None
    for i in player.buffList:
        if i.buffid == 700:
            sheidBuff = i
            break
    myUtil.drawHPRect((255,255,255),(0,255,0),(127,127,127),screenSizeX/2-200,screenSizeY-30,400,10,player.HP,player.maxHP,player.HPDecrease,sheidBuff)
    temp = screenSizeX/2-200
    for i in player.elementList:
        myUtil.drawCDRect((255,255,255),i.getElementColor(),temp,screenSizeY-60,20,i.elementValue,i.elementMax)
        if showInfo:
            if i.reduceSpeed > 0:
                if floor(i.elementValue/i.reduceSpeed) < 10:
                    screen.blit(smallFont.render(str(floor(i.elementValue/i.reduceSpeed)),True,(127,127,127)),(temp+5, screenSizeY-60))
                elif floor(i.elementValue/i.reduceSpeed) < 100:
                    screen.blit(smallFont.render(str(floor(i.elementValue/i.reduceSpeed)),True,(127,127,127)),(temp, screenSizeY-60))
                else:
                    screen.blit(smallFont.render("+",True,(127,127,127)),(temp+5, screenSizeY-60))
            else:
                if floor(i.elementValue/1000) < 10:
                    screen.blit(smallFont.render(str(floor(i.elementValue/1000)),True,(127,127,127)),(temp+5, screenSizeY-60))
                elif floor(i.elementValue/1000) < 100:
                    screen.blit(smallFont.render(str(floor(i.elementValue/1000)),True,(127,127,127)),(temp, screenSizeY-60))
                else:
                    screen.blit(smallFont.render("+",True,(127,127,127)),(temp+5, screenSizeY-60))
        temp = temp + 30
    for i in player.buffList:
        myUtil.drawCDRect((255,255,255),i.buffColor,temp,screenSizeY-60,20,i.buffCurrentTime,i.buffMaxTime)
        if showInfo:
            if floor(i.buffCurrentTime/gFPS) < 10:
                screen.blit(smallFont.render(str(floor(i.buffCurrentTime/gFPS)),True,(127,127,127)),(temp+5, screenSizeY-60))
            elif floor(i.buffCurrentTime/gFPS) < 100:
                screen.blit(smallFont.render(str(floor(i.buffCurrentTime/gFPS)),True,(127,127,127)),(temp, screenSizeY-60))
        temp = temp + 30
    if showInfo:
        if player.HPDecrease-player.HP > 0:
            if sheidBuff is None:
                screen.blit(smallFont.render(str(player.HP)+"/"+str(player.maxHP)+" -"+str(player.HPDecrease-player.HP),True,(255,255,255)),(temp,screenSizeY-60))
            else:
                screen.blit(smallFont.render(str(player.HP)+"+"+str(sheidBuff.buffValue)+"="+str(player.HP+sheidBuff.buffValue)+"/"+str(player.maxHP)+" -"+str(player.HPDecrease-player.HP),True,(255,255,255)),(temp,screenSizeY-60))
        else:
            if sheidBuff is None:
                screen.blit(smallFont.render(str(player.HP)+"/"+str(player.maxHP),True,(255,255,255)),(temp,screenSizeY-60))
            else:
                screen.blit(smallFont.render(str(player.HP)+"+"+str(sheidBuff.buffValue)+"="+str(player.HP+sheidBuff.buffValue)+"/"+str(player.maxHP),True,(255,255,255)),(temp,screenSizeY-60))
    else:
        screen.blit(smallFont.render(str(player.HP),True,(255,255,255)),(temp,screenSizeY-60))
    #渲染玩家元素
    temp = 20
    screen.blit(smallFont.render("元素",True,(255,255,255)),(20, temp))
    for i in player.elementList:
        temp = temp + 30
        myUtil.drawCDRect((127,127,127),i.getElementColor(),20,temp,20,i.elementValue,i.elementMax)
        if showInfo:
            screen.blit(smallFont.render(str(floor(i.elementValue/100.0)/10.0),True,i.getElementColor()),(50, temp))
        else:
            screen.blit(smallFont.render(i.getElementName(),True,i.getElementColor()),(50, temp))
    # 渲染玩家buff
    temp = temp + 30
    screen.blit(smallFont.render("状态",True,(255,255,255)),(20, temp))
    for i in player.buffList:
        temp = temp + 30
        myUtil.drawCDRect((127,127,127),i.buffColor,20,temp,20,i.buffCurrentTime,i.buffMaxTime)
        if showInfo:
            screen.blit(smallFont.render(str(floor(i.buffCurrentTime*10/gFPS)/10.0),True,i.buffColor),(50, temp))
        else:
            screen.blit(smallFont.render(i.buffName,True,i.buffColor),(50, temp))
    #渲染文字
    temp = temp + 30
    screen.blit(smallFont.render("信息",True,(255,255,255)),(20, temp))
    for i in range(len(textList)):
        temp = temp + 30
        screen.blit(baseFont.render(textList[i],True,textListColor[i]),(textListPosX[i],textListPosY[i]))
        if showInfo:
            if temp < screenSizeY - 270:
                screen.blit(smallFont.render(textList[i],True,textListColor[i]),(20,temp))
        else:
            if temp < screenSizeY - 60:
                screen.blit(smallFont.render(textList[i],True,textListColor[i]),(20,temp))
    #渲染时间
    if (datetime.now() - tickFPSTime).seconds >= 1:
        lastActualFPS = actualFPS
        actualFPS = 0
        tickFPSTime = datetime.now()
    if showInfo:
        if lastActualFPS < gFPS:
            screen.blit(smallFont.render("FPS:"+str(lastActualFPS),True,(255,0,0)),(20, screenSizeY-40))
        else:
            screen.blit(smallFont.render("FPS:"+str(lastActualFPS),True,(0,255,0)),(20, screenSizeY-40))
        if mspt * gFPS < 800:
            screen.blit(smallFont.render("MSPT:"+str(mspt),True,(0,255,0)),(20, screenSizeY-70))
        else:
            screen.blit(smallFont.render("MSPT:"+str(mspt),True,(255,0,0)),(20, screenSizeY-70))
        if timeSinceLastDeath/gFPS <= 15.0:
            screen.blit(smallFont.render("活:"+str(floor(timeSinceLastDeath/gFPS))+"s",True,(255,0,0)),(20, screenSizeY-100))
        else:
            screen.blit(smallFont.render("活:"+str(floor(timeSinceLastDeath/gFPS))+"s",True,(0,255,0)),(20, screenSizeY-100))
        if playTime/gFPS/(deathCount+1) <= 60.0:
            screen.blit(smallFont.render("玩:"+str(floor(playTime/gFPS))+"s",True,(255,0,0)),(20, screenSizeY-130))
        else:
            screen.blit(smallFont.render("玩:"+str(floor(playTime/gFPS))+"s",True,(0,255,0)),(20, screenSizeY-130))
        if deathCount <= 0:
            screen.blit(smallFont.render("死:"+str(deathCount)+"次",True,(0,255,0)),(20, screenSizeY-160))
        else:
            screen.blit(smallFont.render("死:"+str(deathCount)+"次",True,(255,0,0)),(20, screenSizeY-160))
        if difficulty/gFPS > 60.0:
            screen.blit(smallFont.render("E:"+str(floor(difficulty*100.0/6/gFPS)/100),True,(255,0,0)),(20, screenSizeY-190))
        else:
            screen.blit(smallFont.render("E:"+str(floor(difficulty*100.0/6/gFPS)/100),True,(0,255,0)),(20, screenSizeY-190))
        if difficulty/6.0/gFPS/gFPS >= 1.0:
            screen.blit(smallFont.render("P:必然",True,(255,0,0)),(20, screenSizeY-220))
        elif difficulty <= 0:
            screen.blit(smallFont.render("P:禁用",True,(255,0,0)),(20, screenSizeY-220))
        else:
            screen.blit(smallFont.render("P:"+str(floor(difficulty*1000.0/6/gFPS/gFPS)/10)+"%",True,(0,255,0)),(20, screenSizeY-220))
        if temp < screenSizeY - 265:
            screen.blit(smallFont.render("TXT:"+str(len(textList)),True,(0,255,0)),(20, screenSizeY-250))
        else:
            screen.blit(smallFont.render("TXT:"+str(len(textList)),True,(255,0,0)),(20, screenSizeY-250))
    else:
        screen.blit(smallFont.render(str(floor(timeSinceLastDeath*10/gFPS)/10.0)+"s",True,(255,255,255)),(20, screenSizeY-40))
    #渲染技能
    myUtil.drawCDRect((0,127,0),(127,127,127),screenSizeX-170,screenSizeY-70,50,player.skillCD[0],player.skillmaxCD[0])
    myUtil.drawCDRect((0,127,0),(127,127,127),screenSizeX-100,screenSizeY-100,80,player.skillCD[1],player.skillmaxCD[1])
    if player.skillCD[0] > 0:
        screen.blit(smallFont.render(str(floor(player.skillCD[0]*10/gFPS)/10.0),True,(255,255,255)),(screenSizeX-159,screenSizeY-55))
    else:
        screen.blit(smallFont.render("E",True,(255,255,255)),(screenSizeX-150,screenSizeY-55))
    if player.skillCD[1] > 0:
        screen.blit(smallFont.render(str(floor(player.skillCD[1]*10/gFPS)/10.0),True,(255,255,255)),(screenSizeX-78,screenSizeY-68))
    else:
        screen.blit(smallFont.render("Q",True,(255,255,255)),(screenSizeX-65,screenSizeY-68))

    player.tick(textList, textListCD, textListColor, textListPosX, textListPosY)
    if not lockDifficulty:
        difficulty = difficulty + 1
        if difficulty > 6*gFPS*gFPS:
            difficulty = 6*gFPS*gFPS
        if difficulty < 0:
            difficulty = 0
    timeSinceLastDeath = timeSinceLastDeath + 1
    actualFPS = actualFPS + 1
    playTime = playTime + 1
    pygame.display.update()
    tickEndTime = datetime.now()
    mspt = (tickEndTime - tickStartTime).microseconds // 1000
    clock.tick(gFPS)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            exit()
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_w:
                myState.w = True
            elif event.key == pygame.K_a:
                myState.a = True
            elif event.key == pygame.K_s:
                myState.s = True
            elif event.key == pygame.K_d:
                myState.d = True
            elif event.key == pygame.K_e:
                if player.skillCD[0] <= 0:
                    player.skillCD[0] = player.skillmaxCD[0]
                    player.damageOrHeal(500)
                    textList.append("+500")
                    textListColor.append((169,232,42))
                    textListCD.append(gFPS * 3)
                    textListPosX.append(player.posX - 80)
                    textListPosY.append(player.posY + 10)
                    player.addBuff(MyBuff(1011, "速", gFPS, gFPS, 1, 100, (245,85,178)))
            elif event.key == pygame.K_q:
                if player.skillCD[1] <= 0:
                    player.skillCD[1] = player.skillmaxCD[1]
                    player.damageOrHeal(1000)
                    player.addElement(3,4000.0,10,1)
                    textList.append("+1000")
                    textListColor.append((169,232,42))
                    textListCD.append(gFPS * 3)
                    textListPosX.append(player.posX - 80)
                    textListPosY.append(player.posY + 10)
                    player.addBuff(MyBuff(1001, "生", 4*gFPS, 4*gFPS, 1, 1000, (181,230,29)))
            elif event.key == pygame.K_SPACE:
                isPaused = True
                textList.append("暂停")
                textListColor.append((255,0,255))
                textListCD.append(gFPS * 3)
                textListPosX.append(screenSizeX / 2 - 20)
                textListPosY.append(100)
            elif event.key == pygame.K_i:
                showInfo = not showInfo
                if showInfo:
                    textList.append("信息:全")
                else:
                    textList.append("信息:略")
                textListColor.append((255,0,255))
                textListCD.append(gFPS * 3)
                textListPosX.append(screenSizeX / 2 - 35)
                textListPosY.append(100)
            elif event.key == pygame.K_l:
                lockDifficulty = not lockDifficulty
                if lockDifficulty:
                    textList.append("难:锁定")
                else:
                    textList.append("难:解锁")
                textListColor.append((255,0,255))
                textListCD.append(gFPS * 3)
                textListPosX.append(screenSizeX / 2 - 35)
                textListPosY.append(100)
            elif event.key == pygame.K_r:
                if difficulty == 0 or difficulty == 1:
                    difficulty = 60*gFPS
                else:
                    difficulty = 1
                textList.append("难:重置")
                textListColor.append((255,0,255))
                textListCD.append(gFPS * 3)
                textListPosX.append(screenSizeX / 2 - 35)
                textListPosY.append(100)
            elif event.key == pygame.K_o:
                difficulty = difficulty + (gFPS * 5)
                if difficulty > 6*gFPS*gFPS:
                    difficulty = 6*gFPS*gFPS
                if difficulty < 0:
                    difficulty = 0
                textList.append("难:增加")
                textListColor.append((255,0,255))
                textListCD.append(gFPS * 3)
                textListPosX.append(screenSizeX / 2 - 35)
                textListPosY.append(100)
            elif event.key == pygame.K_p:
                difficulty = difficulty - (gFPS * 5)
                if difficulty > 6*gFPS*gFPS:
                    difficulty = 6*gFPS*gFPS
                if difficulty < 0:
                    difficulty = 0
                textList.append("难:减少")
                textListColor.append((255,0,255))
                textListCD.append(gFPS * 3)
                textListPosX.append(screenSizeX / 2 - 35)
                textListPosY.append(100)
        elif event.type == pygame.KEYUP:
            if event.key == pygame.K_w:
                myState.w = False
            elif event.key == pygame.K_a:
                myState.a = False
            elif event.key == pygame.K_s:
                myState.s = False
            elif event.key == pygame.K_d:
                myState.d = False