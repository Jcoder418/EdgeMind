import sys
import os

def to_c_array(byte_data, var_name):
    lines = []
    lines.append(f'unsigned char {var_name}[] = {{')
    line = '  '
    for i, b in enumerate(byte_data):
        line += f'0x{b:02x}, '
        if (i + 1) % 12 == 0:
            lines.append(line)
            line = '  '
    if line.strip():
        lines.append(line)
    lines.append('};')
    return '\n'.join(lines)


def write_files(tflite_path, out_cc, out_h, var_name='edgemind_model'):
    with open(tflite_path, 'rb') as f:
        data = f.read()

    c_array = to_c_array(data, var_name)

    # Write .cc
    with open(out_cc, 'w') as f:
        f.write('#include "model.h"\n\n')
        f.write(c_array + '\n')
        f.write(f'unsigned int {var_name}_len = {len(data)};\n')

    # Write .h (lightweight, in case user doesn't want manual edits)
    with open(out_h, 'w') as f:
        f.write('#ifndef MODEL_H\n')
        f.write('#define MODEL_H\n\n')
        f.write(f'extern unsigned char {var_name}[];\n')
        f.write(f'extern unsigned int {var_name}_len;\n\n')
        f.write('#endif // MODEL_H\n')

    print(f'Wrote {out_cc} and {out_h}')


def usage():
    print('Usage: python convert_tflite_to_c.py <tflite_path> [out_cc] [out_h]')


if __name__ == '__main__':
    if len(sys.argv) < 2:
        usage()
        sys.exit(1)

    tflite_path = sys.argv[1]
    out_cc = sys.argv[2] if len(sys.argv) > 2 else 'edgemind_model.cc'
    out_h = sys.argv[3] if len(sys.argv) > 3 else 'model.h'

    if not os.path.exists(tflite_path):
        print('TFLite file not found:', tflite_path)
        sys.exit(2)

    write_files(tflite_path, out_cc, out_h)
