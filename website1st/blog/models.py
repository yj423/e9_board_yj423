from __future__ import unicode_literals
from django.db import models
from django.contrib.auth.models import User,AbstractUser

'''
class UserProfile(models.Model):
    user = models.OneToOneField(User)
    desc = models.TextField(blank = True, null = True)
'''
class User(AbstractUser):
    desc = models.TextField()
    qq = models.TextField()
    cellPhoneNum = models.CharField(max_length = 11)

class Teacher(models.Model):
    id = models.IntegerField(primary_key = True)
    name = models.CharField(max_length=50)
    class Meta:
        #db_table = 'teacher'
        permissions = (('can_view', 'Can see teacher'),
                       ('can_add', 'Can add teacher'),
                       ('can_edit', 'Can edit teacher'),
                       ('can_delete', 'Can delete teacher') )
    def __unicode__(self):
        return str(self.id).ljust(10)+ self.name

# Create your models here.
class Student(models.Model):
    name = models.CharField(max_length = 50)
    age = models.IntegerField()
    #teacher = models.ForeignKey(Teacher, related_name='student_teacher', default = 1)
    teacher = models.ForeignKey(Teacher, default = 1)
    #sex = models.IntegerField()

class Group(models.Model):
    id = models.IntegerField(primary_key = True)
    name = models.CharField(max_length=50)
    members = models.ManyToManyField(Student, through = "Membership")
    class Meta:
        db_table = 'group'

class Membership(models.Model):
    id = models.IntegerField(primary_key = True)
    student = models.ForeignKey(Student, default = 1)
    group = models.ForeignKey(Group, default = 1)
    class Meta:
        db_table = 'membership'

class ReviewManager(models.Manager):
    #def get_quy_set(self):
     #   super(ReviewManager, self).get_query_set().filter(dele=False)

    def all(self):
        return super(ReviewManager, self).exclude(dele=True)
    def review_count(self):
        return self.all().count()

class Review(models.Model):
    user = models.ForeignKey(User)
    student = models.ForeignKey(Student)
    content = models.TextField()
    create_time = models.DateTimeField()
    dele = models.BooleanField(default = 0)

    objects = ReviewManager()

    def __str__(self):
        return self.dele

    def content(self):
        return self.user.username+ "  123 " + self.student.name

    class Meta:
        db_table = "review"
        permissions = (('can_view', 'Can see review'),
                       ('can_add', 'Can add review'),
                       ('can_edit', 'Can edit review'),
                       ('can_delete', 'Can delete review') )

class news(models.Model):
    list_files = ['id', 'news_thread', 'news_title', 'news_url', 'news_time', 'news_from', 'from_url', 'news_body']
    news_thread = models.TextField(blank = True, null = True)
    news_title = models.TextField(blank = True, null = True)
    news_url = models.TextField(blank = True, null = True)
    news_time = models.TextField(blank = True, null = True)
    news_from = models.TextField(blank = True, null = True)
    from_url = models.TextField(blank = True, null = True)
    news_body = models.TextField(blank = True, null = True)
    dele = models.BooleanField(default = 0)

    def __str__(self):
        return models.Models.__str__(self)

    class Meta:
        db_table = "news"





