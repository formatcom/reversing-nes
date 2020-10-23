import os

def Settings(**kwargs):

    return {
        'flags': [
            '-isystem', 'include',
            '-isystem', 'build',
        ]
    }
