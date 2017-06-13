from django.contrib import admin
from blog.models import Student,Teacher,Group,Membership,User


#from django.contrib.auth.models import User

# Register your models here.
'''
class ProfileInline(admin.StackedInline):
    model = UserProfile
    verbose_name = 'profile'

class UserAdmin(admin.ModelAdmin):
    inlines = (ProfileInline,)
'''
admin.site.register(User)
admin.site.register(Student)
admin.site.register(Teacher)
admin.site.register(Group)

'''
admin.site.unregister(User)
admin.site.register(User, UserAdmin)
'''

