TEMPLATE = subdirs

SUBDIRS += \
    editabletreemodel \
    stardelegate


contains(DEFINES, QT_NO_DRAGANDDROP) : SUBDIRS -= puzzle #表示没看懂
!qtHaveModule(xml) : SUBDIRS -= simpledommodel

#contains( variablename, value )
#如果value存在于一个被叫做variablename的变量的值的列表中，那么这个作用域中的设置将会被处理。
#contains( CONFIG, thread ) {        DEFINES += QT_THREAD_SUPPORT    }
#如果thread存在于CONFIG变量的值的列表中时，那么QT_THREAD_SUPPORT将会被加入到DEFINES变量的值的列表中。
