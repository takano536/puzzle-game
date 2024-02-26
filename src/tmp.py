import random
import binascii
import logging


HASH_MAP = tuple(
    'あいうえお'
    'かきくけこ'
    'さしすせそ'
    'たちつてと'
    'なにぬねの'
    'はひふへほ'
    'まみむめも'
    'やゆよ'
    'らりるれろ'
    'わ'
    'がぎぐげご'
    'ざじずぜぞ'
    'だぢづでど'
    'ばびぶべぼ'
)


VALID_HIRAGANA_NUM = len(HASH_MAP)
PASS_CHUNK_SIZE = len(format(VALID_HIRAGANA_NUM - 1, 'b'))
ASCII_CHUNK_SIZE = 8
VALID_LEN_WIDTH = 16
CRC_WIDTH = 32
HEIGHT_WIDTH = 8


def encrypt(field: tuple, objects: dict) -> str:
    FIELD_OBJ_WIDTH = len(format(len(objects) - 1, 'b'))

    h = len(field)
    w = len(field[0])
    logging.debug(f"{h}, {w}")

    valid_len_bits = format(CRC_WIDTH + VALID_LEN_WIDTH + HEIGHT_WIDTH + h * w * FIELD_OBJ_WIDTH, 'b').zfill(VALID_LEN_WIDTH)
    height_bits = format(h, 'b').zfill(HEIGHT_WIDTH)
    field_obj_bits = ''.join(format(objects.get(field[i][j], 0), 'b').zfill(FIELD_OBJ_WIDTH) for i in range(h) for j in range(w))

    bits = valid_len_bits + height_bits + field_obj_bits
    while len(bits) % ASCII_CHUNK_SIZE != 0 or (len(bits) + CRC_WIDTH) % PASS_CHUNK_SIZE != 0:
        bits += '0'

    asc = ''.join(chr(int(bits[i:i+ASCII_CHUNK_SIZE], 2)) for i in range(0, len(bits), ASCII_CHUNK_SIZE))
    logging.debug(asc)
    crc = binascii.crc32(asc.encode('utf-8'))
    logging.debug(f'crc: {crc}')
    crc_bits = format(crc, 'b').zfill(CRC_WIDTH)

    bits = crc_bits + bits
    logging.debug(bits)

    indexes = list(range(CRC_WIDTH, len(bits)))
    random.seed(crc)
    random.shuffle(indexes)
    shffled_bits_str = crc_bits + ''.join(bits[i] for i in indexes)
    logging.debug(shffled_bits_str)

    password = ''.join(HASH_MAP[int(shffled_bits_str[i:i+PASS_CHUNK_SIZE], 2)] for i in range(0, len(shffled_bits_str), PASS_CHUNK_SIZE))
    return password


def decrypt(password: str, objects: dict) -> tuple:
    FIELD_OBJ_WIDTH = len(format(len(objects) - 1, 'b'))
    logging.debug(FIELD_OBJ_WIDTH)

    shffled_bits = str()
    for c in password:
        shffled_bits += format(HASH_MAP.index(c), 'b').zfill(PASS_CHUNK_SIZE)
    logging.debug(shffled_bits)

    crc_bits = shffled_bits[:CRC_WIDTH]
    crc = int(crc_bits, 2)

    bits = list('0' * len(shffled_bits))
    bits[0:CRC_WIDTH] = crc_bits

    indexes = list(range(CRC_WIDTH, len(shffled_bits)))
    random.seed(crc)
    random.shuffle(indexes)
    for i, j in enumerate(indexes):
        bits[j] = shffled_bits[i + CRC_WIDTH]
    bits = ''.join(bits)
    logging.debug(bits)

    asc = ''.join(chr(int(bits[i:i+ASCII_CHUNK_SIZE], 2)) for i in range(CRC_WIDTH, len(bits), ASCII_CHUNK_SIZE))
    logging.debug(asc)
    assert crc == binascii.crc32(asc.encode('utf-8')), 'CRC check failed'

    valid_len = int(bits[CRC_WIDTH:CRC_WIDTH+VALID_LEN_WIDTH], 2)
    height = int(bits[CRC_WIDTH+VALID_LEN_WIDTH:CRC_WIDTH+VALID_LEN_WIDTH+HEIGHT_WIDTH], 2)
    width = (valid_len - CRC_WIDTH - VALID_LEN_WIDTH - HEIGHT_WIDTH) // height // FIELD_OBJ_WIDTH
    logging.debug(f"{valid_len}, {height}, {width}")

    field = list()
    field_bits = bits[CRC_WIDTH+VALID_LEN_WIDTH+HEIGHT_WIDTH:]
    for i in range(height):
        row = str()
        for j in range(width):
            filed_bits_idx = i * width * FIELD_OBJ_WIDTH + j * FIELD_OBJ_WIDTH
            obj_idx = int(field_bits[filed_bits_idx:filed_bits_idx+FIELD_OBJ_WIDTH], 2)
            row += next(k for k, v in objects.items() if v == obj_idx)
        field.append(row)

    return tuple(field)


def main():

    # FIELD = (
    #     "WWWWWWWW",
    #     "W.....WW",
    #     "W.W.WP.W",
    #     "W.HP.W.W",
    #     "W......W",
    #     "W.....WW",
    #     "W......W",
    #     "WWWWWWWW",
    # )
    OBJS = {
        '.': 0,
        'W': 1,
        'H': 2,
        'P': 3,
    }

    logging.basicConfig(level=logging.DEBUG)
    logging.disable(logging.CRITICAL)
    # password = encrypt(FIELD, OBJS)
    # print(password)
    password = input().strip()
    assert set(password) <= set(HASH_MAP), 'Invalid character in password'
    decrypt(password, OBJS)
    for row in decrypt(password, OBJS):
        print(row)


if __name__ == '__main__':
    main()
