#vim: set fileencoding=utf-8
import unohelper
from com.sun.star.task import XJob

import traceback
import dialog
from datetime import date


g_ImplementationHelper = unohelper.ImplementationHelper()

Color = {"Yellow":16776960, "White":-1, "RED":16711680, "Table":3394764}

def parseDate(str):
    try:
        tmp = [int(v) for v in str.split('-')]
    except:
        tmp = [int(v) for v in str.split('/')]
    finally:
        if len(tmp) != 3:
            dialog.ShowError(str + "不是合法日期格式")
    return date(tmp[0], tmp[1], tmp[2])


def writeFormula(sheet, col, row, data):
  	cell = sheet.getCellByPosition(col, row)
   	cell.Formula = data
def getCellString(sheet, col, row):
    cell = sheet.getCellByPosition(col, row)
    return cell.getString().strip()
def changeRowBGColor(sheet, row, color):
  	r = sheet.getRows().getByIndex(row)
   	r.CellBackColor = color
def changeRowFGColor(sheet, row, color):
  	r = sheet.getRows().getByIndex(row)
   	r.CharColor = color
def showAll(sheet):
    rows = sheet.getRows()
    for r in range(10000):
       rows.getByIndex(r).IsVisible = True

def countExpireUser(state, basedate, date_, employee, info):
    eee = info["employee"].get(employee, [0, 0])  # [149, 33]
    if date_ >= basedate:
        eee[0] += 1 #隶属次员工数
        info["expire"] += 1
    if state == "已续费":
		eee[1] += 1
		info["ok"] += 1
    elif state == "拆迁":
        info["goaway"] += 1
        info["expire"] -= 1 
    elif state == "续开中":
        info["goaway"] += 1
        info["expire"] -= 1
        if employee: 
            info["ok"] += 1
            eee[1] += 1
        else:
            info["gohome"] += 1
			  	
def drawTable(cellRange, color):
    newborder = cellRange.TopBorder
    newborder.OuterLineWidth = 2
    cellRange.TopBorder = newborder
    cellRange.BottomBorder = newborder
    cellRange.LeftBorder = newborder
    cellRange.RightBorder = newborder
    cellRange.CellBackColor = color

def isValidTable(l_id, begin, sheet):
    if l_id  == 0:
        dialog.ShowError("小子打dota打晕了吧 你确定这是张艾普续费统计表吗!")
        return False
    if begin == -1:
        dialog.ShowError("没有发现‘dummy’标记,自动添加标记\n"+\
                        "若标记错误请手动更改否则更新表格时可能会出现问题\n"+\
                        "此标记在手动添加数据时候加快查找速度\n"+\
                        "      在生成统计表时确定开始行数\n"+\
                         "dummy标记会在生成最终文档时自动去掉")
        writeFormula(sheet, 0, l_id+8, "dummy")
        return False
    return True


class MySheet():
    def __init__(self, sheet):
    	self.sheet = sheet
        self.IDs = {}
        self.Begin = -1
        self.employee = {}
        for i in range(1, 10000):
            data = getCellString(sheet, 0, i)
            if data == 'dummy':
                self.Begin = i
                break
            elif data:
                self.IDs[data] = i
                e = getCellString(self.sheet, 5, i).encode('utf-8')
                if e:
                    self.employee[e] = True

        isValidTable(len(self.IDs), self.Begin, self.sheet)

    def markOK(self, id, amount, time, cahsier, date):
        row = self.IDs[id]
        self.sheet.getCellByPosition(4, row).setFormula("已续费")
        self.sheet.getCellByPosition(5, row).setFormula(cahsier)
        self.sheet.getCellByPosition(6, row).setFormula(amount)
        self.sheet.getCellByPosition(7, row).setFormula(time)
        self.sheet.getCellByPosition(8, row).NumberFormat=33
        self.sheet.getCellByPosition(8, row).setFormula(\
            parseDate(date).isoformat())
        self.sheet.getCellByPosition(8, row).HoriJustify="RIGHT"
        changeRowBGColor(self.sheet, row, Color["Yellow"])
        changeRowFGColor(self.sheet, row, -1)
    def markRemove(self, id):
        row = self.IDs[id]
        self.sheet.getCellByPosition(4, row).setFormula("拆迁")
        changeRowFGColor(self.sheet, row, Color["RED"])
        changeRowBGColor(self.sheet, row, -1)


class AddItem(unohelper.Base, XJob):
    def __init__(self, ctx):
        desktop = ctx.ServiceManager.createInstanceWithContext(
            "com.sun.star.frame.Desktop", ctx)
        self.document = desktop.getCurrentComponent()
        self.sheet = MySheet(self.document.getSheets().getByIndex(0))

    def execute(self, args):
        try:
            d = dialog.addItem()
            today = date.today().strftime("%Y-%m-%d")
            d.getControl('t_date').setText(today)
            n = d.getControl('t_cashier')
            i = 0
            for k,v in self.sheet.employee.items():
                n.addItem(k, i)
                i += 1
            if (d.execute()):
                id = d.getControl('t_id').getText()
                amount = d.getControl('t_amount').getText()
                time = d.getControl('t_time').getText()
                cashier  = d.getControl('t_cashier').getSelectedItem()
                date_ = d.getControl('t_date').getText()
                self.sheet.markOK(id, amount, time, cashier, date_)
        except:
            error = traceback.format_exc()
            dialog.ShowError(error)

class RemoveItem(unohelper.Base, XJob):
    def __init__(self, ctx):
        desktop = ctx.ServiceManager.createInstanceWithContext(
            "com.sun.star.frame.Desktop", ctx)
        self.document = desktop.getCurrentComponent()
        self.sheet = MySheet(self.document.getSheets().getByIndex(0))
    def execute(self, args):
        try:
            d = dialog.removeItem()
            if (d.execute()):
                id = d.getControl('t_id').getText()
                self.sheet.markRemove(id)
        except:
            error = traceback.format_exc()
            dialog.ShowError(error)

class UpdateItem(unohelper.Base, XJob):
    def __init__(self, ctx):
        desktop = ctx.ServiceManager.createInstanceWithContext(
            "com.sun.star.frame.Desktop", ctx)
        self.document = desktop.getCurrentComponent()
        self.sheet = self.document.getSheets().getByIndex(0) 
        self.IDs = {}
        self.employee = {}
        self.Begin = -1
        for i in range(1, 10000):
            data = getCellString(self.sheet, 0, i)
            if data == 'dummy':
                self.Begin = i
                break
            elif data:
                self.IDs[data] = i
                e = getCellString(self.sheet, 5, i).encode('utf-8')
                if e:
                    self.employee[e] = True
        self.month = {"expire":0, "goaway":0, "ok":0, "gohome":0, "employee":{}}
        self.half = {"expire":0, "goaway":0, "ok":0, "gohome":0, "employee":{}}
        for v in self.employee:
            self.month["employee"][v] = [0, 0]
            self.half["employee"][v] = [0, 0]

        isValidTable(len(self.IDs), self.Begin, self.sheet)

    def writeTable(self, begin, info):
        alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        s = self.sheet
        writeFormula(s, 1, begin+1, "到期")
        writeFormula(s, 1, begin+2, "已续费")
        writeFormula(s, 1, begin+3, "续费率")
        writeFormula(s, 2, begin, "总计")
        writeFormula(s, 2, begin+1, info["expire"])
        writeFormula(s, 2, begin+2, info["ok"])
        writeFormula(s, 2, begin+3, "={2}{0}/{2}{1}".format(begin+3, begin+2,\
                                                            alphabet[2]))
        self.sheet.getCellByPosition(2, begin+3).NumberFormat=11

        e = info["employee"]
        i = 2
        for v in e:
            i += 1
            p1 = info["employee"][v][0]
            p2 = info["employee"][v][1]
            writeFormula(s, i, begin, v)
            writeFormula(s, i, begin+1, p1)
            writeFormula(s, i, begin+2, p2)
            writeFormula(s, i, begin+3,
                         "={2}{0}/{2}{1}".format(begin+3, begin+2, alphabet[i])) 
            self.sheet.getCellByPosition(i, begin+3).NumberFormat=11
        i += 1
        pp1 = info["goaway"] 
        pp2 = info["gohome"]
        writeFormula(s, i, begin, "拆迁用户".encode('gb18030'))
        writeFormula(s, i, begin+1, pp1)
        writeFormula(s, i, begin+2, pp2)
        writeFormula(s, i, begin+3, 
                     "={2}{0}/{2}{1}".format(begin+3, begin+2, alphabet[i]))
        self.sheet.getCellByPosition(i, begin+3).NumberFormat=11 
        cellrange = self.sheet.getCellRangeByPosition(1, begin, i, begin+3)
        drawTable(cellrange, Color["Table"])


    def countAll(self):
        for i in self.IDs :
            row = self.IDs[i]
            state = getCellString(self.sheet, 4, row).encode('utf-8')
            date_ = getCellString(self.sheet, 12, row)
            employee = getCellString(self.sheet, 5, row).encode('utf-8')
            now = date.today()

            middle_m = date(now.year, now.month, 15)
            countExpireUser(state, parseDate(date_), middle_m, 
                            employee, self.half) 

            if now.month != 2:
                try: full_m = date(now.year, now.month, 31)
                except: full_m = date(now.year, now.month, 30)
            else:
                try: full_m = date(now.year, now.month, 29) 
                except: full_m = date(now.year, now.month, 28)
            countExpireUser(state, parseDate(date_), full_m,
                            employee, self.month)

    def execute(self, args):
        try:
            self.countAll()
            writeFormula(self.sheet, 1, self.Begin+15, "全月到期")
            self.writeTable(self.Begin+15, self.month)
            writeFormula(self.sheet, 1, self.Begin+20, "月中到期")
            self.writeTable(self.Begin+20, self.half)
            dialog.ShowError("OK 当前生成的只是测试用表")
        except:
            error = traceback.format_exc()
            dialog.ShowError(error)

class NetFetch(unohelper.Base, XJob):
    def __init__(self, ctx):
        desktop = ctx.ServiceManager.createInstanceWithContext(
            "com.sun.star.frame.Desktop", ctx)
        self.document = desktop.getCurrentComponent()
    def execute(self, args):
        try:
            self.sheet = self.document.getSheets().getByIndex(0)
            showAll(self.sheet)
        except:
            error = traceback.format_exc()
            dialog.ShowError(error)

g_ImplementationHelper.addImplementation(\
        NetFetch, "org.snyh.pyuno.autogo.net",
                ("com.sun.star.task.Job",),)
g_ImplementationHelper.addImplementation( \
        AddItem, "org.snyh.pyuno.autogo.add",
                ("com.sun.star.task.Job",),)
g_ImplementationHelper.addImplementation( \
        RemoveItem, "org.snyh.pyuno.autogo.remove",
                ("com.sun.star.task.Job",),)
g_ImplementationHelper.addImplementation( \
        UpdateItem, "org.snyh.pyuno.autogo.update",
                ("com.sun.star.task.Job",),)
