#!/usr/bin/env python2

import rospy 
from std_msgs.msg import Int16, Int32, Int64

k = 0
n = 4


def publisher():  
    global k
    while not rospy.is_shutdown():

        #This part is use to optimize the network traffic 
        #if k is larger than the range of Int16, publicher will change the type of msg (Int16,32,64) in order to utilize the data space
        if (k > -32767 and k < 32767 ):
            pub = rospy.Publisher('GUO', Int16, queue_size=10)
        elif (k > -2147483648 and k < 2147483648):
            pub = rospy.Publisher('GUO', Int32, queue_size=10)
        else:
            pub = rospy.Publisher('GUO', Int64, queue_size=10)

        pub.publish(k)
        k = k + n
        rate.sleep()

    

if __name__ == "__main__":
    rospy.init_node('nodeA')
    rate = rospy.Rate(20) # 20hz

    publisher()
