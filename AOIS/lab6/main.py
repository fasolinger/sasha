class MyHashTable:
    ALPHA = 'АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ'

    class Node:
        def __init__(self, key, val, nxt=None):
            self.key = key
            self.val = val
            self.nxt = nxt

    def __init__(self, size: int):
        self.size = size
        self.table = [None] * self.size

    def hash_func(self, key: str) -> int:
        index = sum([self.ALPHA.index(c) for c in key.lower()])
        return index % self.size

    def get(self, key: str) -> str:
        index = self.hash_func(key)
        node = self.table[index]
        while node:
            if node.key == key:
                return node.val
            node = node.nxt
        raise KeyError(key)

    def put(self, key: str, val: str) -> None:
        index = self.hash_func(key)
        node = self.table[index]
        while node:
            if node.key == key:
                node.val = val
                return
            node = node.nxt
        new_node = self.Node(key, val)
        new_node.nxt = self.table[index]
        self.table[index] = new_node

    def remove(self, key: str) -> None:
        hash_key = self.hash_func(key)
        node = self.table[hash_key]
        if not node:
            raise KeyError(key)

        prev = None
        while node:
            if node.key == key:
                if prev:
                    prev.nxt = node.nxt
                else:
                    self.table[hash_key] = node.nxt
                return
            prev, node = node, node.nxt

        raise KeyError(key)

    def print_table(self) -> None:
        for i in range(self.size):
            node = self.table[i]
            elements = []
            while node:
                elements.append((node.key, node.val))
                node = node.nxt
            print(elements)

    
    if __name__ == '__main__':
    my_table = MyHashTable(10)

    my_table.put("Дифференциал", 'анализ')
    my_table.put("Функция", 'анализ')
    my_table.put("Деление", 'алгебра')
    my_table.put("Умножение", 'алгебра')
    my_table.put("Матрица", 'линейная алгебра')
    my_table.put("Вектор", 'линейная алгебра')
    my_table.put("Ребро", 'теория графов')
    my_table.put("Узел", 'теория графов')
    my_table.put("Кортеж", 'теория множеств')
    my_table.put("Множество", 'теория множеств')

    print(my_table.get("Ребро"))
    print(my_table.get("Умножение"))
    print(my_table.get("Функция"))
    my_table.print_table()
