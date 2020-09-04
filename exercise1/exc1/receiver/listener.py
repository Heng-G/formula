#!/usr/bin/env python2

import rospy 
from std_msgs.msg import Float32, Int16

q =0.15

def callback(num):
    
    result = num.data/q
    print result
    pub.publish(result)


def listen():  
    rospy.Subscriber('GUO', Int16, callback)

  


if __name__ == "__main__":
    rospy.init_node('nodeB')
    pub = rospy.Publisher('/kthfs/result', Float32, queue_size=10)
    rate = rospy.Rate(20) # 20hz

    listen()

    rospy.spin()
    


