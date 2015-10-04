# SentimentAnalysis
Hadoop + Python to Perform Sentiment Analysis

## Dependencies

- [Google Test](https://code.google.com/p/googletest/)
- [Oleandar Stemming Library](https://github.com/OleanderSoftware/OleanderStemmingLibrary)


## How to build
```
git clone --recursive https://github.com/AcidLeroy/SentimentAnalysis.git
cd SentimentAnalysis
mkdir build
cd build
cmake ..
make -j3
make test
```

## How to use the mapper
```bash
./bin/mapper < ../files/input.txt > output.txt
#Reducer only works on sorted output
cat output.txt | sort > sorted_output.txt
```
## How to use the reducer
```bash
./bin/reducer.py < sorted_output.txt
```

