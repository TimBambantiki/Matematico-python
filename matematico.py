# -*- coding: utf-8 -*-
#!/usr/bin/python

from Tkinter import *
import matematico


class App:
	cislo = 0;
	kolo = 0;
	body = 0;

	master = None

	def __init__(self, master):
		self.master = master
		self.menu()

		self.tableFrame = Frame(master, background="#000000")
		self.tableFrame.grid(row=0, column=0)


		self.vykresliTabulku()

		self.skoreFrame = Frame(master)
		self.skoreFrame.grid(row=0, column=1)
		self.cisloLabel = Label(self.skoreFrame, text="", font="Arial 20")
		self.cisloLabel.grid(row=0, column=0)

		resetButton = Button(self.skoreFrame, text=u"Nová hra", command=self.reset)
		resetButton.grid(row=1, column=0)

		self.dalsiKolo()

	def dalsiKolo(self):
		if(self.kolo<matematico.pocetKol()):
			self.kolo = self.kolo+1
			self.cislo = matematico.generujCislo()
			self.cisloLabel.config(text=self.cislo)
		else:
			self.spocitejSkore()

	def spocitejSkore(self):
		self.body = matematico.sectiBody()
		self.cisloLabel.config(text=u"Skore:"+str(self.body))

	def vykresliTabulku(self):
		self.table = []
		velikost = matematico.velikostPole()

		for row in range(0, velikost):
			for col in range(0, velikost):
				self.table.append(TabButton(self, self.tableFrame, row, col))

	def reset(self):
		matematico.restart()
		self.kolo = 0

		for button in self.table:
			button.reset()

		self.dalsiKolo()

	def menu(self):
		menu = Menu(self.master)

		menuHra = Menu(menu)

		menu.add_cascade(label="Hra", menu=menuHra)


		#menu.add_command(label="Ahoj!", command=hello)
		#menu.add_command(label="Pryč!", command=root.destroy)

		self.master.config(menu=menu)



class TabButton:
	app		= 	None
	button	=	None
	x	 	=	None
	y		=	None
	value	=	None

	def __init__(self, app, parent, x, y):
		self.app = app
		self.x = x
		self.y = y

		self.button = Button(parent, text=self.value, command=self.save, width=4, height=2, background="black", font=("Times", 20, "bold"))
		self.button.grid(row=x, column=y)

	def save(self):
		self.button.config(text=app.cislo, state="disabled")
		matematico.ulozSouradnice(self.x, self.y, app.cislo)

		app.dalsiKolo()

	def reset(self):
		self.button.config(text="", state="normal")





if __name__=="__main__":
	root = Tk()
	root.title("Matematico")
	app = App(root)
	root.mainloop()

