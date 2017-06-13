from django.conf.urls import url
from . import views

urlpatterns = [
    url(r'^index/$',views.index),
    url(r'^login/$',views.login, name='login'),
    url(r'^register/$',views.register, name='register'),
    url(r'^time/$', views.time),
    url(r'^foo/(\d{4})/(\w+)/$', views.foo),
    url(r'^bar/(?P<id>\d{4})/(?P<name>\w+)/$', views.bar),
    url(r'^student_list/$', views.student_list),
    url(r'^add_news/$', views.add_news),
    url(r'^modify_news/$', views.modify_news),
    url(r'^remove_news/$', views.remove_news),
    url(r'^search_news/$', views.search_news),
    url(r'^add_review/$', views.add_review),
    url(r'^review_detail/$', views.review_detail),
]