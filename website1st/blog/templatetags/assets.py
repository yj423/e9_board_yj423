from django import template
from website1st.settings import IS_DEVELOP

register = template.Library()

# check whether the environment is development environment
@register.filter
def assets(value):
    if IS_DEVELOP:
        return "/blog/"+ value;
    return "/blog/assets/" + value
