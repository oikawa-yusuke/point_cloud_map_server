#include <iostream>
#include <string>

#include <ros/ros.h>

// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>

int main(int argc, char** argv)
{
  ros::init (argc, argv, "my_pcl_tutorial");
  ros::NodeHandle nh;
  ros::NodeHandle pnh("~");
  ros::Publisher pub = nh.advertise<sensor_msgs::PointCloud2> ("points2", 1);
  double x_cloud; double y_cloud; double z_cloud; 
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  std::string file_name = "input_filename.pcd";
  pnh.getParam("filename", file_name);
  pcl::io::loadPCDFile<pcl::PointXYZ> (file_name, *cloud);

  sensor_msgs::PointCloud2::Ptr message (new sensor_msgs::PointCloud2);
  
  sensor_msgs::PointCloud2 object_msg;
  pcl::toROSMsg(*cloud.get(), *message );
  message->header.frame_id = "world";

  ros::Rate loop_rate(4);

  while (ros::ok())
  {
    //msg->header.stamp = ros::Time::now().toNSec();
    pub.publish (message);
    ros::spinOnce ();
    loop_rate.sleep ();
  }
}