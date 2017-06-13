# -*- coding: utf-8 -*-
from django.shortcuts import render,render_to_response
from django.http import HttpResponse,HttpResponseRedirect
from django.template import loader, Context
import datetime
import uuid
from django import forms
from blog.models import Student,Teacher,Group,Membership,User,news,Review
from django.contrib.auth.models import Permission
from django.db.models import Q
from django.db import connection,connections,transaction

def register(request):
    if('email' or 'pwd') not in request.GET:
        lf = LoginForm()
        return render_to_response('register.html', {'lf': lf,  "custom_name": "Yan Jun"})
    lf = LoginForm(request.GET)
    email = lf.data['email']
    pwd = lf.data['pwd']
    #Create a user
    user = User()
    user.username = uuid.uuid1()
    user.email = email
    user.set_password(pwd)
    user.desc = 'lazy'
    user.save()
    user.user_permissions = [Permission.objects.get(codename='can_view'),
                             Permission.objects.get(codename='can_add')]
    user.save()
    return HttpResponseRedirect("/blog/login")

class LoginForm(forms.Form):
    email = forms.CharField(label="email:", max_length = 100)
    pwd = forms.CharField(label ="password:", widget=forms.PasswordInput)
    age = forms.IntegerField(label="age", max_value=100,min_value=1)

    def clean(self):
        email = self.cleaned_data.get('email')
        print(len(email))
        if len(email.spilt('@')) < 2:
            raise forms.ValidationError("Email is NOT legal")
        return email


"""
class LoginForm(forms.Form, forms.ModelForm):
    email = forms.CharField(label="email:", max_length = 100)
    pwd = forms.CharField(label ="password:", widget=forms.PasswordInput)
"""
def login(request):
    if ('email' or 'pwd') not in request.GET:
        lf = LoginForm()
        return render_to_response('login.html', {'lf': lf})
    lf = LoginForm(request.GET)
    email = lf.data['email']
    pwd = lf.data['pwd']

    """
    print (email + " "+ pwd)
    userList  = User.objects.all()
    for user in userList:
        print("email:" + user.email)
    """

    try:
        user = User.objects.get(email=email)

    except User.DoesNotExist:
        print("User doesn't exist")
        pass
    else:
        if user.check_password(pwd):
            #check permissions
            if user.has_perm("blog.can_delete"):
                # do something when you have the permissions
                return  HttpResponse("you can delete teacher")
            else:
                return  HttpResponse("you can NOT delete teacher")
           # return HttpResponse("login in:" + user.email)
    return HttpResponseRedirect("/blog/login")

class Person(object):
    def __init__(self, name, age, sex):
        self.name = name
        self.age = age
        self.sex = sex
    def say(self):
        return "my name is" + self.name

# Create your views here.
def index(request):
    t = loader.get_template('index.html')
    user = {'sex':'male', 'name':'Jone','age':'29'}
    #c = Context({'title':'django', 'name':'Jone'})
    person = Person('',15,'female')

    bookList = ["python","ruby","perl","java"]
    #bookList = []


    #book_list2 = []
    #for book in bookList:
    #    book_list2.append(book.upper)

    c = Context({'title':'django', 'user':user, 'book_list':bookList, 'today': datetime.datetime.now()})
    #return HttpResponse("<h1>Hello World111</h1>")
    return HttpResponse(t.render(c))

def time(request):
    t = loader.get_template('time.html')
    id = request.GET.get("id")
    name = request.GET.get("name")
    c = Context({ 'today': datetime.datetime.now(), "id":id, "name":name})
    return HttpResponse(t.render(c))

def foo(request, id, name):
    t = loader.get_template('time.html')
    c = Context({ 'today': datetime.datetime.now(), "id":id, "name":name})
    return HttpResponse(t.render(c))

def bar(request, id, name):
    t = loader.get_template('time.html')
    c = Context({ 'today': datetime.datetime.now(), "id":id, "name":name})
    return HttpResponse(t.render(c))


def student_list(request):
    print ('here\n')

    #update
    '''
    student = Student.objects.get(id = 1)
    student.name = 'tom'
    student.age = 30
    student.save()  """
    '''
    #delete
    '''
    student = Student.objects.get(id = 2)
    student.delete()
    '''

    #delete in batch
    '''
    deleteStudent = Student.objects.all().filter(name__exact = "xyz")
    if deleteStudent is not None:
        deleteStudent.delete()
    else:
        print ("delteStudent is None")
    '''
    #add
    '''
    newstu = Student(name = 'abcdef', age = 10)
    newstu.save()
    '''

    # Update in batch
    #studentList = Student.objects.all().filter(age__lt = 40).update (name = 'xyz')

    #studentList = Student.objects.all()
    teacher = Teacher.objects.get(id =1)
    studentList = teacher.student_set.all()
    #student = teacher.student_set.get(id = 1)
    #student.delete()
    #student.teacher.delete()

    # one mapped to multiple
    '''
    teacher.student_set.create(name = 'tom')
    student = Student(name = "tom")
    teacher.student_set.add(student)
    '''
    '''
    group = Group.objects.get(id = 1)
    studentList = group.member.all()
    groupList = student.group_set.all()

    # add a new connection
    Membership(group = newGroup, student=newStudent).save();
    '''
    t = loader.get_template('student_list.html')
    c = Context({"studentList": studentList})
    #studentList= Student.objects.get(id = 2)
    #t = loader.get_template('student_list.html')
    #studentList= Student.objects.all().filter(name__exact = 'zhangsan')
    #studentList= Student.objects.all().filter(age__te = 40)
    #studentList= Student.objects.all().filter(age__gt = 21)
    #studentList= Student.objects.all().filter(age = 22)
    #studentList= Student.objects.all().order_by("-age", "id")
    #studentList= Student.objects.all().order_by("-age")
    #studentList = Student.object.all().order_by("age")
    #c = Context({"studentList": studentList})

    return HttpResponse(t.render(c))

def add_news(request):
    n = news( news_thread = 'Shanghai',
        news_title = '爆炸',
        news_url = 'http://news.sina.com/201509090',
        news_time = '2017.05.07',
        news_body = '爆炸案导致腾讯机房故障')
    n.save()
    return HttpResponse('success')

def modify_news(request):
    n = news.objects.get(news_url = 'http://news.sina.com/201509090')
    if not n:
         return HttpResponse('failure')

    n.news_body= '今天没吃药'
    n.save()
    return HttpResponse('success')

def remove_news(request):
    n = news.objects.get(news_url = 'http://news.sina.com/201509090')
    if not n:
         return HttpResponse('failure')

    n.delete()
    return HttpResponse('success')

'''
def search_news(request):
    news_list = news.objects.filter( Q(news_title = '爆炸') | Q(news_body = '腾讯机房'))
    res_str = ''
    for n in news_list:
        res_str += '<br>' + n.news_body

    return HttpResponse(res_str)
'''
def search_news(request):
   # news_list = news.objects.raw('select * from news where id = 7 ')
    #sql = 'select * from news where id = 7 '
    #cursor = connection.cursor()
    #cursor.execute(sql)
    #news_list = cursor.fetchall()
    res_str = ''
    #for n in news_list:
        #res_str += '<br>' + n[3]
    #res_str = str(Review.objects.review_count())

    review_list = Review.objects.all()
    for new in review_list:
       res_str += '<br>' + new.content()
    return HttpResponse(res_str)

def add_review(request):
    user = User.objects.get(id = 1)
    stu = Student.objects.get(id = 1)
    rev = Review(user = user,
                student = stu,
                create_time = datetime.datetime.now())
    rev.save()
    return HttpResponse("success add review")



def review_detail(request):
    review_id = 1
    #revs = Review.objects.filter(id =review_id)
    #通过外键筛选
    revs = Review.objects.filter(user__username='yanjun')
    response_str = ''
    for review in revs:
        response_str += '<br> List'
        response_str += '<br>review_id:'+ str(review.id)
        response_str += '<br>username:'+ review.user.username
    return HttpResponse(response_str)

