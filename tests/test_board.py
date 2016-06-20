import unittest
import random
import keys

class TestBoard(unittest.TestCase):
    '''
    Tests the c interface to the board,
    and hopefully tests the c code in the
    process
    '''
    def setUp(self):
        self.board = keys.new_board()

    def tearDown(self):
        keys.free_board(self.board)

    @staticmethod
    def random_location():
        '''
        returns a tuple with a random x and y between
        0 and 7 inclusive
        '''
        return (random.randrange(0,8), random.randrange(0,8))
    @staticmethod
    def random_x():
        '''
        returns a tuple with a random x and y between
        0 and 7 inclusive
        '''
        return random.randrange(0,8)
    @staticmethod
    def random_y():
        '''
        returns a tuple with a random x and y between
        0 and 7 inclusive
        '''
        return random.randrange(0,8)

    def test_adding_key(self):
        pass
