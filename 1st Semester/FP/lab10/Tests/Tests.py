import unittest
from src.Repository.Repository import repository
from src.Domain.Moves import mills
from src.Domain.Moves import moves
from src.Domain.Oponent import oponent
from src.Services.Services import services

class Test(unittest.TestCase):
    def test_is_game_over(self):
        """
        tests the is_game_over function
        :return:
        """
        repo=repository()
        mill = mills()
        move = moves()
        oponents= oponent(repo, mill, move)
        service=services(repo, mill, move, oponents)
        self.assertEqual(service.is_game_over(),True)
        service.manage_add_piece(1)
        service.oponent_phase_1()
        service.manage_add_piece(24)
        service.oponent_phase_1()
        service.manage_add_piece(11)
        service.oponent_phase_1()
        self.assertEqual(service.is_game_over(),True)
    def test_add_piece(self):
        """
        tests the add_piece function
        :return:
        """
        repo=repository()
        mill = mills()
        move = moves()
        oponents= oponent(repo, mill, move)
        service=services(repo, mill, move, oponents)
        service.manage_add_piece(1)
        self.assertEqual(repo.get_board()[1],'X')
        self.assertEqual(repo.get_board()[2], '_')
    def test_remove_piece(self):
        """
        tests the remove_piece function
        :return:
        """
        repo = repository()
        mill = mills()
        move = moves()
        oponents = oponent(repo, mill, move)
        service = services(repo, mill, move, oponents)
        service.manage_add_piece(1)
        service.manage_remove_piece(1)
        self.assertEqual(repo.get_board()[1], '_')
    def test_check_move(self):
        """
        tests the check_move function
        :return:
        """
        repo = repository()
        mill = mills()
        move = moves()
        oponents = oponent(repo, mill, move)
        service = services(repo, mill, move, oponents)
        self.assertEqual(service.check_move(1),[2,10])
        service.manage_add_piece(1)
        self.assertEqual(service.check_move(1), [2,10])
    def test_check_mill(self):
        """
        tests the check_mill function
        :return:
        """
        repo = repository()
        mill = mills()
        move = moves()
        oponents = oponent(repo, mill, move)
        service = services(repo, mill, move, oponents)
        service.manage_add_piece(1)
        service.manage_add_piece(2)
        service.manage_add_piece(3)
        service.manage_add_piece(4)
        self.assertEqual(service.check_mill(1),True)
        self.assertEqual(service.check_mill(2), True)
        self.assertEqual(service.check_mill(3), True)
        self.assertEqual(service.check_mill(4), False)
    def test_oponent_phase_1(self):
        """
        tests the oponent_phase_1 function
        :return:
        """
        repo = repository()
        mill = mills()
        move = moves()
        oponents = oponent(repo, mill, move)
        service = services(repo, mill, move, oponents)
        service.manage_add_piece(1)
        service.oponent_phase_1()
        self.assertEqual(service.count_pieces_oponent(), 1)
    def test_oponent_phase_2(self):
        """
        tests the oponent_phase_2 function

        :return:
        """
        repo = repository()
        mill = mills()
        move = moves()
        oponents = oponent(repo, mill, move)
        service = services(repo, mill, move, oponents)
        service.manage_add_piece(1)
        service.oponent_phase_1()

        service.oponent_phase_2()
        self.assertEqual(service.count_pieces_oponent(),1)
    def test_count_pieces(self):
        """
        tests the count_pieces function

        :return:
        """
        repo = repository()
        mill = mills()
        move = moves()
        oponents = oponent(repo, mill, move)
        service = services(repo, mill, move, oponents)
        service.manage_add_piece(1)
        self.assertEqual(service.count_pieces(),1)
    def test_count_pieces_oponent(self):
        """
        tests the count_pieces_oponent function
        :return:
        """
        repo = repository()
        mill = mills()
        move = moves()
        oponents = oponent(repo, mill, move)
        service = services(repo, mill, move, oponents)
        service.manage_add_piece(1)
        service.oponent_phase_1()
        self.assertEqual(service.count_pieces_oponent(),1)
    def test_get_board(self):
        """
        tests the get_board function

        :return:
        """
        repo = repository()
        mill = mills()
        move = moves()
        oponents = oponent(repo, mill, move)
        service = services(repo, mill, move, oponents)

        self.assertEqual(service.get_board(),repo.get_board())\

    def test_minimax_phase2(self):
        """
        tests the minimax_phase2 function

        :return:
        """
        repo = repository()
        mill = mills()
        move = moves()
        oponents = oponent(repo, mill, move)
        service = services(repo, mill, move, oponents)

        service.manage_add_piece(1)
        service.oponent_phase_1()
        service.oponent_phase_2()
        self.assertEqual(service.count_pieces_oponent(), 1)
    def test_update_board(self):
        """
        tests the update_board function
        :return:

        """
        repo = repository()
        mill = mills()
        move = moves()
        oponents = oponent(repo, mill, move)
        service = services(repo, mill, move, oponents)

        service.manage_add_piece(1)
        service.oponent_phase_1()
        service.oponent_phase_2()
        self.assertEqual(service.count_pieces_oponent(), 1)
    def test_inc_depth(self):
        """
        tests the inc_depth function
        :return:
        """
        repo = repository()
        mill = mills()
        move = moves()
        oponents = oponent(repo, mill, move)
        oponents.inc_depth()
        self.assertEqual(oponents.get_depth(),1)

    def test_get_board(self):
        """
        tests the get_board function

        :return:
        """
        repo = repository()
        mill = mills()
        move = moves()
        oponents = oponent(repo, mill, move)
        self.assertEqual(oponents.get_board(),repo.get_board())

    def test_get_depth(self):
        """
        tests the get_depth function

        :return:
        """
        repo = repository()
        mill = mills()
        move = moves()
        oponents = oponent(repo, mill, move)
        self.assertEqual(oponents.get_depth(),0)
    def test_minimax_phase1(self):
        """
        tests the minimax_phase1 function
        :return:
        """
        repo = repository()
        mill = mills()
        move = moves()
        oponents = oponent(repo, mill, move)
        service = services(repo, mill, move, oponents)

        service.manage_add_piece(1)
        oponents.minimax_phase1(repo.get_board(),0,-10000,10000,False)
        self.assertEqual(oponents.get_depth(),0)
    def test_minimax_phase2(self):
        """
        tests the minimax_phase2 function

        :return:
        """
        repo = repository()
        mill = mills()
        move = moves()
        oponents = oponent(repo, mill, move)
        service = services(repo, mill, move, oponents)

        service.manage_add_piece(1)
        service.oponent_phase_1()
        service.oponent_phase_2()
        self.assertEqual(service.count_pieces_oponent(), 1)
    def test_make_move_1(self):
        """
        tests the make_move function

        :return:
        """
        repo = repository()
        mill = mills()
        move = moves()
        oponents = oponent(repo, mill, move)
        service = services(repo, mill, move, oponents)
        service.manage_add_piece(1)
        oponents.make_move_1(service.get_board())
        self.assertEqual(oponents.get_board()[1],'X')
        self.assertEqual(oponents.get_board()[2],'_')
    def test_make_move_2(self):
        """
        tests the make_move function
        :return:
        """
        repo = repository()
        mill = mills()
        move = moves()
        oponents = oponent(repo, mill, move)
        oponents.inc_depth()
        service = services(repo, mill, move, oponents)
        service.manage_add_piece(1)
        service.oponent_phase_1()
        oponents.make_move_2(service.get_board())
        self.assertEqual(oponents.get_board()[1], 'X')
        self.assertEqual(oponents.get_board()[2], '_')






