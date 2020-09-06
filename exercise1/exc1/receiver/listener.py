#!/usr/bin/env python2

import rospy 
from std_msgs.msg import UInt16, Float32

q =0.15

def callback(num):
    
    result = num.data/q
    print result
    publish(result)
    


def publish(result):
    pub.publish(result)
    rate.sleep()


if __name__ == "__main__":
    rospy.init_node('nodeB')
    pub = rospy.Publisher('/kthfs/result', Float32, queue_size=10)
    rate = rospy.Rate(20) # 20hz
    rospy.Subscriber('GUO', UInt16, callback)



    rospy.spin()
    



