# SentimentAnalysis
Spark + Python to Perform Sentiment Analysis

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
```
./src/mapper/mapper ../files/stop_words.txt < ../files/input.txt > output.txt
```
## How to use the reducer
./src/reducer/reducer < output.txt

