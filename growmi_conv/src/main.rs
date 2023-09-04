use image::{io::*, GenericImageView};
use std::fs::File;
use std::io::*;
const FILE_NAME: &str = "map0002.png";
const PURPLE_BRICK: u8 = 69;
const TRANSPARENT: u8 = 255;
fn grey_scale_write(fs: &mut File, pixel: u8, value: &str) {
    write!(fs, "tilemap->map[{pixel}] = 0x{value};\n").unwrap();
}

fn main() {
    let name = &FILE_NAME[0..FILE_NAME.len() - 4];
    let mut output_file = File::create(format!("{}.h",name)).unwrap();
    write!(&mut output_file, "void load_level(gfx_tilemap_t *tilemap) {{").unwrap();
    println!("dir: {}", format!("levels/{}", FILE_NAME));
    let mut img = Reader::open(format!("levels/{}", FILE_NAME)).unwrap().decode().unwrap().to_luma8();
    let pix = img.pixels();
    let mut index = 0;
    for i in pix {
        match i.0[0] {
            PURPLE_BRICK => grey_scale_write(&mut output_file, index, "02" ),
            TRANSPARENT => grey_scale_write(&mut output_file, index, "03" ),
            _ => panic!()
        }
        index += 1;
        println!("{}", i.0[0]);
    }
    write!(&mut output_file, "}}\n").unwrap();
    output_file.flush().unwrap();
}
