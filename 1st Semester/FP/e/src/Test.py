import unittest
from src.Repository import Repository
class Tests(unittest.TestCase):
    def Test_first_year(self):
        self.repo=Repository()
        self.assertEquals(self.repo.year,1)
        self.assertEquals(self.repo.population,1000)
        self.assertEquals(self.repo.rats,20)

    def Test_New_year(self):
        self.repo=Repository()
        self.repo.new_year()
        self.assertEquals(self.repo.year,2)

    def Test_Get_year(self):
        self.repo=Repository
        k=self.repo.get_year()
        self.assertEquals(k,1)


if __name__=='__main__':
    unittest.main()