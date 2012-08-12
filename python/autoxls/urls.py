from django.conf.urls.defaults import patterns, include, url
from workxls import  views
# Uncomment the next two lines to enable the admin:
from django.contrib import admin
admin.autodiscover()

urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'autoxls.views.home', name='home'),
    # url(r'^autoxls/', include('autoxls.foo.urls')),
    #('^hello/$' , views.hello),
    ('^admin/$' , views.genXLS),
   # (r'^search/$' ,views.search ),
    #(r'search-form/$' , views.search_form),
    (r'^(\w+)/$' , views.makexls),
    (r'^css/(?P<path>.*)', 'django.views.static.serve',{'document_root': r'.\templates'}),
    (r'^js/(?P<path>.*)', 'django.views.static.serve',{'document_root': r'.\templates'})
    # Uncomment the admin/doc line below to enable admin documentation:
    #url(r'^admin/doc/', include('django.contrib.admindocs.urls')),

    # Uncomment the next line to enable the admin:
    #url(r'^admin/', include(admin.site.urls)),
)
