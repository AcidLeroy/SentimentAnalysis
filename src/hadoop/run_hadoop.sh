#!/bin/bash
mapper=~/SentimentAnalysis/build/bin/mapper
reducer=~/SentimentAnalysis/build/bin/reducer.py

hdfs_dir=/users/ceilar/aclImdb/train/pos/
hdfs_out=/users/ceilar/train_pos/

streaming=${HADOOP_HOME}/share/hadoop/tools/lib/hadoop-streaming-2.6.0.jar

hadoop jar ${streaming} -file ${mapper} -mapper ${mapper} -file ${reducer} -reducer ${reducer} -input $hdfs_dir* -output ${hdfs_out}
