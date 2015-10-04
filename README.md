/********************************************************************************/
			SENTIMENT ANALYSIS, CS 567
/********************************************************************************/
# SentimentAnalysis
Spark + Python to Perform Sentiment Analysis

## Dependencies

- [Google Test](https://code.google.com/p/googletest/)
- [Oleandar Stemming Library](https://github.com/OleanderSoftware/OleanderStemmingLibrary)


/**********************************/
		MAPPER
/**********************************/
## How to build mapper
```
git clone https://github.com/AcidLeroy/SentimentAnalysis.git
git clone https://github.com/OleanderSoftware/OleanderStemmingLibrary.git
cd SentimentAnalysis
mkdir build
cd build
cmake .. -DOLEANDAR_STEMMING=~/<your_repo_dir>/OleanderStemmingLibrary
make -j3
make test
```

## How to use the mapper
```
./src/mapper/mapper ../files/stop_words.txt < ../files/input.txt > output.txt
```

/**********************************/
		REDUCER
/*********************************/
## How to build reducer
g++ -o reducer reducer.cpp
## Using Reducer
./reducer

