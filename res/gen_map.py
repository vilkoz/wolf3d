#!/usr/bin/env python3

import random

def randint(a, b):
    if a < b:
        return random.randint(a, b)
    return a

MIN_SIZE = 6

class Node:

    def __init__(self, x1, x2, y1, y2):
        self.childs = []
        self.border = ((x1, y1), (x2, y2))
        self.room = None
        self.connected = False

    def split(self, iteration):
        w = self.border[1][0] - self.border[0][0]
        h = self.border[1][1] - self.border[0][1]
        if iteration <= 0:
            return
        if not (w > h and w / h >= 1.25) or (h > w and h / w >= 1.25) or \
                randint(0, 1):
            if (h / 2) <= MIN_SIZE:
                return 
            self.split_vert(iteration)
        else:
            if (w / 2) <= MIN_SIZE:
                return 
            self.split_hor(iteration)

    def split_vert(self, iteration):
        percent = randint(40, 60) / 100
        dist = self.border[1][1] - self.border[0][1]
        split_coord = self.border[0][1] + int(dist * percent)
        self.childs.append(Node(self.border[0][0], self.border[1][0],
            self.border[0][1], split_coord))
        self.childs.append(Node(self.border[0][0], self.border[1][0],
            split_coord, self.border[1][1]))
        for elem in self.childs:
            elem.split(iteration - 1)

    def split_hor(self, iteration):
        percent = randint(40, 60) / 100
        dist = self.border[1][0] - self.border[0][0]
        split_coord = self.border[0][0] + int(dist * percent)
        self.childs.append(Node(self.border[0][0], split_coord,
            self.border[0][1], self.border[1][1]))
        self.childs.append(Node(split_coord, self.border[1][0],
            self.border[0][1], self.border[1][1]))
        for elem in self.childs:
            elem.split(iteration - 1)

    def draw_border(self, m):
        for y in range(self.border[0][1], self.border[1][1] + 1):
            for x in range(self.border[0][0], self.border[1][0] + 1):
                if x == self.border[0][0] or x == self.border[1][0] or \
                y == self.border[0][1] or y == self.border[1][1]:
                    m[y][x] = '2'
        for child in self.childs:
            child.draw_border(m)

    def make_rooms(self):
        if (len(self.childs) != 0):
            for child in self.childs:
                child.make_rooms()
        else:
            w = self.border[1][0] - self.border[0][0]
            h = self.border[1][1] - self.border[0][1]
            gap_size = [0, 0]
            if w - w // 4 > MIN_SIZE:
                gap_size[0] = min([3, w // 4])
            if h - h // 4 > MIN_SIZE:
                gap_size[1] = min([3, h // 4])
            self.room = (
                    (
                        1 + self.border[0][0] + randint(0, gap_size[0]),
                        1 + self.border[0][1] + randint(0, gap_size[1])
                    ),
                    (
                        self.border[1][0] - 1 - randint(0, gap_size[0]),
                        self.border[1][1] - 1 - randint(0, gap_size[1])
                    )
            )

    def draw_room(self, m):
        if (self.room):
            for y in range(self.room[0][1], self.room[1][1]+1):
                for x in range(self.room[0][0], self.room[1][0]+1):
                    if y == self.room[0][1] or y == self.room[1][1] \
                    or x == self.room[0][0] or x == self.room[1][0]:
                        m[y][x] = '*'
                    else:
                        m[y][x] = ' '
        else:
            for child in self.childs:
                child.draw_room(m)

    def draw_room_walls(self, m):
        if (self.room):
            wall = "12345"[randint(0, 4)]
            for y in range(self.room[0][1], self.room[1][1]+1):
                for x in range(self.room[0][0], self.room[1][0]+1):
                    if y == self.room[0][1] or y == self.room[1][1] \
                    or x == self.room[0][0] or x == self.room[1][0]:
                        if m[y][x] not in ['D', 'd', '_']:
                            m[y][x] = wall if randint(0, 1000) < 990 else '6'
        else:
            for child in self.childs:
                child.draw_room_walls(m)

    def get_center(self):
        w = self.border[1][0] - self.border[0][0]
        h = self.border[1][1] - self.border[0][1]
        return (
                self.border[0][0] + w // 2,
                self.border[0][1] + h // 2
        )

    def connect_pair(self, a, b, m, doors=False):
        c_a = a.get_center()
        c_b = b.get_center()
        p1 = [min(c_a[0], c_b[0]), max(c_a[0], c_b[0])]
        p2 = [min(c_a[1], c_b[1]), max(c_a[1], c_b[1])]
        for y in range(p2[0], p2[1] + 1):
            for x in range(p1[0], p1[1] + 1):
                if doors and m[y][x] == '*' and p1[0] == p1[1]:
                    m[y][x] = 'd'
                elif doors and m[y][x] == '*':
                    m[y][x] = 'D'
                elif m[y][x] not in ['D', 'd']:
                    m[y][x] = '_'
        for node in [a, b]:
            if len(node.childs) == 0:
                node.connected = True

    def get_child_pairs(self):
        for i in range(len(self.childs)):
            for j in range(len(self.childs)):
                if i != j:
                    yield (self.childs[i], self.childs[j])

    def dig_hall(self, m):
        if (len(self.childs) <= 1):
            return
        if (len(self.childs) == 2):
            a = self.childs[0]
            b = self.childs[1]
        if (len(self.childs) == 2) and len(a.childs) == 0 and len(b.childs) == 0:
                self.connect_pair(a, b, m, doors=True)
        else:
            for pair in self.get_child_pairs():
                self.connect_pair(pair[0], pair[1], m)
        for c in self.childs:
            c.dig_hall(m)

    def get_first_child(self):
        if len(self.childs) == 0:
            return self
        return self.childs[0].get_first_child()

    def get_last_child(self):
        if len(self.childs) == 0:
            return self
        return self.childs[len(self.childs) - 1].get_first_child()

    def get_rooms(self):
        if self.room:
            return [self]
        rooms = []
        for c in self.childs:
            rooms += c.get_rooms()
        return rooms

    def place_zombies(self, m):
        if randint(0, 5) > 1:
            size = max([self.room[1][0] - self.room[0][0], self.room[1][1] - self.room[0][1]])
            num = randint(3, size)
            for _ in range(num):
                p = [
                        randint(self.room[0][0] + 1, self.room[1][0] - 1),
                        randint(self.room[0][1] + 1, self.room[1][1] - 1)
                ]
                m[p[1]][p[0]] = 'z'

def put_player(n, m):
    s = n.get_first_child()
    m[randint(s.room[0][1] + 2, s.room[1][1] - 2)][randint(s.room[0][0] + 2, s.room[1][0] - 2)] = 'P'

def put_exit(n, m):
    s = n.get_last_child()
    if randint(0, 1):
        rand_1 = randint(s.room[0][1] + 1, s.room[1][1] - 1)
        rand_2 = randint(0, 1)
        while m[rand_1][s.room[rand_2][0]] == '_':
            rand_1 = randint(s.room[0][1] + 1, s.room[1][1] - 1)
            rand_2 = randint(0, 1)
        m[rand_1][s.room[rand_2][0]] = '8'
    else:
        rand_1 = randint(0, 1)
        rand_2 = randint(s.room[0][0] + 1, s.room[1][0] - 1)
        while m[s.room[rand_1][1]][rand_2] == '_':
            rand_1 = randint(0, 1)
            rand_2 = randint(s.room[0][0] + 1, s.room[1][0] - 1)
        m[s.room[rand_1][1]][rand_2] = '8'

def replace_halls(m):
    for i, row in enumerate(m):
        for j, el in enumerate(row):
            if el == '_':
                m[i][j] = ' '
            if el == '*':
                m[i][j] = '2'

def count_zombies(m):
    z = 0
    for row in m:
        for el in row:
            if el == 'z':
                z += 1
    return z

def place_sprites(m):
    for i, row in enumerate(m):
        for j, el in enumerate(row):
            if el == ' ':
                if i - 1 > 0 and m[i-1][j] not in ['d', 'D'] \
                and i + 1 > 0 and m[i+1][j] not in ['d', 'D'] \
                and j - 1 > 0 and m[i][j-1] not in ['d', 'D'] \
                and j + 1 > 0 and m[i][j+1] not in ['d', 'D']:
                    if randint(0, 100) > 95:
                            m[i][j] = 'b'
                    elif randint(0, 1000) > 999:
                        m[i][j] = 'a'
    z_num = int(count_zombies(m) // 3)
    while z_num > 0:
        for i, row in enumerate(m):
            for j, el in enumerate(row):
                if z_num <= 0:
                    break
                if el == ' ':
                    if i - 1 > 0 and m[i-1][j] not in ['d', 'D'] \
                    and i + 1 > 0 and m[i+1][j] not in ['d', 'D'] \
                    and j - 1 > 0 and m[i][j-1] not in ['d', 'D'] \
                    and j + 1 > 0 and m[i][j+1] not in ['d', 'D']:
                        if randint(0, 1000) > 999:
                            m[i][j] = 's'
                            z_num -= 1
                        elif randint(0, 1000) > 999:
                            m[i][j] = 'h'
                            z_num -= 1
            if z_num <= 0:
                break
        if z_num <= 0:
            break

def check_no_hall(p, size, m, index):
    if index in [1, 2]:
        size += 1
    for x in range(p[0] + 1, p[0] + size - 1):
        for y in range(p[1] + 1, p[1] + size - 1):
            if m[y][x] == '_':
                return False
    return True

def draw_secret_room(p, size, m, index):
    if index in [1, 2]:
        size += 1
    for x in range(p[0] + 1, p[0] + size - 1):
        for y in range(p[1] + 1, p[1] + size - 1):
            if randint(0, 1):
                m[y][x] = 's' if randint(0, 5) > 3 else 'h'
            else:
                m[y][x] = ' '

def place_secret_door(p, index, m):
    deltas = [[0, 1], [-1, 0], [0, -1], [1, 0]]
    delta = deltas[index]
    p1 = [p[0] + 1, p[1] + 1]
    while m[p1[1]][p1[0]] in ['h', 's', ' ']:
        p1 = [x1 + x2 for x1, x2 in zip(delta, p1)]
    m[p1[1]][p1[0]] = '7'

def place_secret_room(n, m):
    nodes = n.get_rooms()
    for r in nodes:
        gaps = [
                r.room[0][1] - r.border[0][1] + 1,
                r.border[1][0] - r.room[1][0],
                r.border[1][1] - r.room[1][1],
                r.room[0][0] - r.border[0][0] + 1
                ]
        w = r.border[1][0] - r.border[0][0]
        h = r.border[1][1] - r.border[0][1]
        is_enough_size = [x > 3 for x in gaps]
        if is_enough_size.count(True) >= 1 and True:#randint(0, 10) > 3:
            index = is_enough_size.index(True)
            if index == 0:
                p = [
                        randint(r.room[0][0] + 1, r.room[1][0] - 1 - gaps[index]),
                        r.border[0][1] 
                ]
                count = 0
                while not check_no_hall(p, gaps[0], m, index):
                    p = [
                            randint(r.room[0][0] + 1, r.room[1][0] - 1 - gaps[index]),
                            r.border[0][1] 
                    ]
                    count += 1
                    if count >= 10:
                        return
            elif index == 2:
                p = [
                        randint(r.room[0][0] + 1, r.room[1][0] - 1 - gaps[index]),
                        r.border[1][1] - gaps[index]
                ]
                count = 0
                while not check_no_hall(p, gaps[index], m, index):
                    p = [
                            randint(r.room[0][0] + 1, r.room[1][0] - 1 - gaps[index]),
                            r.border[1][1] - gaps[index]
                    ]
                    count += 1
                    if count >= 10:
                        return
            elif index == 1:
                p = [
                        r.border[1][0] - gaps[index],
                        randint(r.room[0][1] + 1, r.room[1][1] - 1 - gaps[index])
                    ]
                count = 0
                while not check_no_hall(p, gaps[index], m, index):
                    p = [
                            r.border[1][0] - gaps[index],
                            randint(r.room[0][1] + 1, r.room[1][1] - 1 - gaps[index])
                        ]
                    count += 1
                    if count >= 10:
                        return
            elif index == 3:
                p = [
                        r.border[0][0],
                        randint(r.room[0][1] + 1, r.room[1][1] - 1 - gaps[index])
                    ]
                count = 0
                while not check_no_hall(p, gaps[index], m, index):
                    p = [
                            r.border[0][0],
                            randint(r.room[0][1] + 1, r.room[1][1] - 1 - gaps[index])
                        ]
                    count += 1
                    if count >= 10:
                        return

            draw_secret_room(p, gaps[index], m, index)
            place_secret_door(p, index, m)

size = 50
world = []
for _ in range(size):
    row = []
    for __ in range(size):
        row.append(1)
    world.append(row)


n = Node(0, size - 1, 0, size - 1)
n.split(4)
n.draw_border(world)
n.make_rooms()
n.draw_room(world)
n.dig_hall(world)
n.draw_room_walls(world)
put_player(n, world)
place_secret_room(n, world)
replace_halls(world)
rooms = n.get_rooms()
for node in rooms[1:]:
    node.place_zombies(world)
place_sprites(world)
put_exit(n, world)

for row in world:
    for el in row:
        print(el, end='')
    print("")
