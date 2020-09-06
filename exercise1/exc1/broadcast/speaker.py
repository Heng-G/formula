#!/usr/bin/env python2

import rospy 
from std_msgs.msg import UInt16

k = 0
n = 4


def publisher():  
    global k
    while not rospy.is_shutdown():

   
        pub.publish(k)
        k = k + n
        rate.sleep()

if __name__ == "__main__":
    rospy.init_node('nodeA')
    pub = rospy.Publisher('GUO', UInt16, queue_size=10)
    rate = rospy.Rate(20) # 20hz

    publisher()
