# -*- coding: utf-8 -*-
from django.http import HttpResponse
from django.shortcuts import  render_to_response,HttpResponseRedirect
from datetime import  date
import datetime

def hello(request):
    now = datetime.datetime.now()
    return HttpResponse(str(now))

def makexls(request , name):
    gl_dict = {'chengcheng':'孙成成',
               'yuanzhi':'区远志',
               'dongping':'吴东平',
               'tingting':'项婷婷',
               'yunxin':'俞云新'}
    week = ['星期一','星期二','星期三','星期四','星期五','星期六','星期日']
    html_content={}
    html_content['name'] = gl_dict[name]
    html_content['project'] = u'广东平台维保服务'
    html_content['date'] = date.isoformat(date.today())
    html_content['week'] = week[date.weekday(date.today())]
    html_content['worktype'] = 'PROG'
    if gl_dict.has_key(name) == False:
        return HttpResponse("Error!");
    return render_to_response('workxls.html' , html_content)

def search_form(request):
    return  render_to_response("search_form.html")

def search(request):
    if 'q' in request.GET:
        message = 'You searched for %s' %request.GET['q']
    else:
        message = 'You submit a empty word!'
    return  HttpResponse(message)

def genXLS(request):
    return HttpResponse("Hello!")