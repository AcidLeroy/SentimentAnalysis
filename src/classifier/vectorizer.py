#/usr/bin/python

import subprocess
from signal import signal, SIGPIPE, SIG_DFL
import pandas
import csv
import numpy as np
import os 

def get_array(file_name, sent_type): 
    """ 
    file_name = file to the data.
    sent_type = sentiment type (+1 for positive -1 for negative review)
    """
    data = pandas.read_csv(file_name, sep='\t', quoting=csv.QUOTE_NONE, names=["word", "counts"])
    mat = np.ones(len(data))*sent_type; 
    data['type'] = mat
    return data; 

def strip(text):
    """
    Remove training whitespace
    """
    try:
        return text.strip()
    except AttributeError:
        return text

def get_vocab_idx(vocab_data, word): 
    try: 
        return vocab_data[vocab_data["vocab"] == word].index.tolist()[0]
    except: 
        return 0; 

def create_vocab(vocab_data, data_frame): 
    """
    vocab_data = The data frame representing the vocabulary
    data_frame = The data frame representing the training data
    In this step we convert the words to their integer representation in the vocabulary.
    """
    indices = []
    for word in data_frame["word"]: 
        indices.append(get_vocab_idx(vocab_data, word))
    
    data_frame['integer'] = indices; 
    return data_frame
    

def vectorizer(file_name, path_to_mapper, path_to_reducer, path_to_vocab):
    out_file = "out.txt"
    bash_cmd = "cat {} | {} | sort | {} > {}".format(file_name, path_to_mapper, path_to_reducer, out_file)    
    #print(bash_cmd)
    output = subprocess.call(
        bash_cmd,
        shell = True,
        preexec_fn = lambda: signal(SIGPIPE, SIG_DFL)
        )
    sent_type = 0; 
    if "train/pos" or "test/pos" in file_name: 
        sent_type = 1 
    else: 
        sent_type = -1;

    #print("Sent type is : {}".format(sent_type));

    data = get_array(out_file, sent_type)
    vocab_data = pandas.read_csv(path_to_vocab, sep='\n', quoting=csv.QUOTE_NONE, names=["vocab"], converters={'vocab' : strip})
    vocab_data = vocab_data.drop_duplicates()
    
    data = data.sort(['counts'], ascending=0).head(5000)
    data = create_vocab(vocab_data, data)

    from sklearn.feature_extraction.text import TfidfTransformer
    transformer = TfidfTransformer()
    x_data = transformer.fit_transform(data[['integer', 'counts']].values)

    y_data = data[['type']].values
    # y_data needs to be in the shape of (samples,)
    y_data = y_data.ravel()
    os.remove(out_file)
    return (x_data, y_data)
    

file_name = "/Users/cody/Downloads/aclImdb/train/pos/9_7.txt"
path_to_mapper = "/Users/cody/Repos/SentimentAnalysis/build/bin/mapper"
path_to_reducer = "/Users/cody/Repos/SentimentAnalysis/build/bin/reducer.py"
path_to_vocab = "/Users/cody/Repos/SentimentAnalysis/files/stemmed_vocab.txt"

vectorizer(file_name, path_to_mapper, path_to_reducer, path_to_vocab); 
