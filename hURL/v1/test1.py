# -*- coding: utf-8 -*-
"""
Created on Thu Dec 22 19:48:53 2011

@author: sunday
"""

from sqlalchemy import create_engine,ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column, Integer, String
from sqlalchemy.orm import sessionmaker

engine = create_engine("sqlite:///d:\\hurl\\dbfile",echo = True)
Base = declarative_base()
session = sessionmaker(bind=engine)()

class User(Base):
    __tablename__ = 'users'
    id = Column(Integer, primary_key=True)
    name = Column(String)
    fullname = Column(String)
    password = Column(String)
    def __init__(self, name, fullname, password):
        self.name = name
        self.fullname = fullname
        self.password = password
    def __repr__(self):
        return "<User('%s','%s', '%s')>" % (self.name, self.fullname, self.password)
class Phone(Base):
    __tablename__ = 'phones'
    id = Column(Integer,primary_key = True)
    uid = Column(Integer,ForeignKey(User.id))
    phone = Column(String(32))
    def __init__(self,uid,phone):
        self.uid = uid
        self.phone = phone
    def __repr__(self):
        return "<Phones('%s','%s')>" %(self.uid,self.phone)

Phone.metadata.create_all(engine)
User.metadata.create_all(engine)
u1=User('Sunday','SunChengCheng','sun')
#session = Session()
session.add(u1)
session.commit()

def test(site):
    s='\w*[.]' + site + '$|^' + site + '$'
    print s
    txt = raw_input("Please input txt\n")
    pattern = re.compile(s)
    m = re.match(pattern,txt)
    if m == None :
        print "None"
    else:
        print m.start()
