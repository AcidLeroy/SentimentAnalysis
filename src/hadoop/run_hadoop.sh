#!/bin/bash
mapper=~/Repos/SentimentAnalysis/build/bin/mapper
reducer=~/Repos/SentimentAnalysis/build/bin/reducer.py

hdfs_dir=/user/cody/train_unsup/
hdfs_out=/user/cody/train_unsup_out/

streaming=${HADOOP_HOME}/libexec/share/hadoop/tools/lib/hadoop-streaming-2.6.0.jar

hadoop jar ${streaming} -file ${mapper} -mapper ${mapper} -file ${reducer} -reducer ${reducer} -input $hdfs_dir* -output ${hdfs_out}
