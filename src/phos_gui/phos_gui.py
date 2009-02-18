#!/usr/bin/env python
import sys
import copy

from PyQt4 import QtCore, QtGui, uic
from PhosConst import *

window_class, base_class = uic.loadUiType("phos_gui.ui")

class phosGui(QtGui.QMainWindow, window_class):

    def __init__(self, *args):
        QtGui.QMainWindow.__init__(self, *args)

        self.setupUi(self)

        print self.frame_rcu_top.height()
        print self.frame_rcu_top.width()
        print self.frame_rcu_top.x()
        print self.frame_rcu_top.y()
        

        self.buildGui()

    def buildGui(self):
        
        self.pushButton_fee = [None]*(4*5)

        self.initTabs()
    
        self.initModules()

    def initTabs(self):

        
        self.module_tabs = [None]*5
        
        self.module_tabs[0] = self.tab_module_0

        for i in range(1,5):
            
            self.module_tabs[i] = QtGui.QWidget()
            
            self.tab_modules.addTab(self.module_tabs[i], "Module " + str(i))


    def initModules(self):

        for i in range(5):
            
            self.initRcus(i)
        
    def initRcus(self, moduleId):
        
        self.rcu_frames = range(4)

        self.rcu_lines = range(4*4)


        tmpQrect = copy.deepcopy(self.frame_rcu0.geometry())

        tmpQrectLine0 = copy.deepcopy(self.rcu_line_0.geometry())
        tmpQrectLine1 = copy.deepcopy(self.rcu_line_1.geometry())
        tmpQrectLine2 = copy.deepcopy(self.rcu_line_2.geometry())
        tmpQrectLine3 = copy.deepcopy(self.rcu_line_3.geometry())

        height = tmpQrect.height()

        for i in range(4):

            self.rcu_frames[i] = QtGui.QFrame(self.module_tabs[moduleId])
            self.rcu_lines[i*4] = QtGui.QFrame(self.rcu_frames[i])
            self.rcu_lines[i*4+1] = QtGui.QFrame(self.rcu_frames[i])
            self.rcu_lines[i*4+2] = QtGui.QFrame(self.rcu_frames[i])
            self.rcu_lines[i*4+3] = QtGui.QFrame(self.rcu_frames[i])

            if i > 0:
                tmpQrect.setY(tmpQrect.y() + height) 

            tmpQrect.setHeight(height)

            self.rcu_frames[i].setGeometry(tmpQrect)
            self.rcu_lines[i*4].setGeometry(tmpQrectLine0)
            self.rcu_lines[i*4+1].setGeometry(tmpQrectLine1)
            self.rcu_lines[i*4+2].setGeometry(tmpQrectLine2)
            self.rcu_lines[i*4+3].setGeometry(tmpQrectLine3)            

            self.rcu_frames[i].setFrameRect(self.frame_rcu0.frameRect())
            self.rcu_frames[i].setFrameShadow(self.frame_rcu0.frameShadow())
            self.rcu_frames[i].setFrameShape(self.frame_rcu0.frameShape())

            self.rcu_lines[i*4].setFrameShape(self.rcu_line_0.frameShape())
            self.rcu_lines[i*4+1].setFrameShape(self.rcu_line_1.frameShape())
            self.rcu_lines[i*4+2].setFrameShape(self.rcu_line_2.frameShape())
            self.rcu_lines[i*4+3].setFrameShape(self.rcu_line_3.frameShape())
            

            self.initFee(i)
            #self.initTru(i)
            #self.initRcuButtons(i)
        
    def initFee(self, rcuId):

        tmpQrect = copy.deepcopy(self.fee_1_a.geometry())

        self.pushButton_fee[rcuId] = [None]*28

        
        for i in range(14):

            self.pushButton_fee[rcuId][i] = QtGui.QPushButton(self.rcu_frames[rcuId])
            if i > 0:
                tmpQrect.setX(tmpQrect.x()+11)
            tmpQrect.setWidth(16)
            self.pushButton_fee[rcuId][i].setGeometry(tmpQrect)
            self.pushButton_fee[rcuId][i].setText(hex(i+1)[2:].upper())

        tmpQrect = copy.deepcopy(self.fee_1_b.geometry())
        print tmpQrect.height()
        for i in range(14):

            self.pushButton_fee[rcuId][i+14] = QtGui.QPushButton(self.rcu_frames[rcuId])
            if i > 0:
                tmpQrect.setX(tmpQrect.x()+11)
            tmpQrect.setWidth(16)
            self.pushButton_fee[rcuId][i+14].setGeometry(tmpQrect)
            self.pushButton_fee[rcuId][i+14].setText(hex(i+1)[2:].upper())
        
#     def initTru(self, rcuId):

#         tmpQrect = copy.deepcopy(self.fee_1_a.geometry())

#         self.pushButton_fee[rcuId] = [None]*28

        
#         for i in range(14):

#             self.pushButton_fee[rcuId][i] = QtGui.QPushButton(self.rcu_frames[rcuId])
#             if i > 0:
#                 tmpQrect.setX(tmpQrect.x()+11)
#             tmpQrect.setWidth(16)
#             self.pushButton_fee[rcuId][i].setGeometry(tmpQrect)
#             self.pushButton_fee[rcuId][i].setText(hex(i+1)[2:].upper())

#         tmpQrect = copy.deepcopy(self.fee_1_b.geometry())

#         for i in range(14):

#             self.pushButton_fee[rcuId][i+14] = QtGui.QPushButton(self.rcu_frames[rcuId])
#             if i > 0:
#                 tmpQrect.setX(tmpQrect.x()+11)
#             tmpQrect.setWidth(16)
#             self.pushButton_fee[rcuId][i+14].setGeometry(tmpQrect)
#             self.pushButton_fee[rcuId][i+14].setText(hex(i+1)[2:].upper())
