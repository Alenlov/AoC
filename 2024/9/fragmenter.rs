use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;



#[derive(Eq, Hash, PartialEq, Clone)]
struct Data {
    start: i64,
    length: i64,
    id: i64,
}

fn print_current(mut data_files : Vec<Data>, mut free_space : Vec<Data>) {
    let mut total_data : Vec<Data> = Vec::new();
    total_data.append(&mut data_files);
    total_data.append(&mut free_space);
    total_data.sort_by_key(|d| d.start);
    for d in total_data {
        if d.id != -1 {
            print!("{}",d.id.to_string().repeat(d.length as usize));
        } else {
            print!("{}",".".repeat(d.length as usize));
        }
    }
    print!("\n");
}

fn print_current_comp(mut data_files : Vec<Data>, mut free_space : Vec<Data>, mut compressed : Vec<Data>) {
    let mut total_data : Vec<Data> = Vec::new();
    total_data.append(&mut data_files);
    total_data.append(&mut free_space);
    total_data.append(&mut compressed);
    total_data.sort_by_key(|d| d.start);
    for d in total_data {
        if d.id != -1 {
            print!("{}",d.id.to_string().repeat(d.length as usize));
        } else {
            print!("{}",".".repeat(d.length as usize));
        }
    }
    print!("\n");
}

fn calc_hash(data_files : Vec<Data>) -> i64 {
    let mut res : i64 = 0;
    for d in data_files {
        res += d.id * d.length * (2*d.start + d.length - 1)/2;
    }
    return res;
}

fn compress(mut data_files : Vec<Data>, mut free_space : Vec<Data>) -> i64 {
    let mut empty_id : usize = 0;
    let mut compressed : Vec<Data> = Vec::new();
    while data_files.len() > 0 {
        let mut last_data = data_files.pop().unwrap();
        while last_data.length > 0 {
            
            let free_data = &mut free_space[empty_id];
            if free_data.start > last_data.start {
                compressed.push(last_data);
                break;
            }
            if free_data.length >= last_data.length {
                let compressed_data = Data{start : free_data.start, length : last_data.length, id : last_data.id};
                free_data.start += last_data.length;
                free_data.length -= last_data.length;
                last_data.length -= last_data.length;
                compressed.push(compressed_data);
            } else if free_data.length > 0 {
                let compressed_data = Data{start : free_data.start, length : free_data.length, id : last_data.id};
                free_data.start += free_data.length;
                last_data.length -= free_data.length;
                free_data.length -= free_data.length;
                compressed.push(compressed_data);
            } else {
                empty_id += 1;
            }
        } 
    }
    
    return calc_hash(compressed);
}

fn compress_b(mut data_files : Vec<Data>, mut free_space : Vec<Data>) -> i64 {
    let mut empty_id : usize;
    let mut compressed : Vec<Data> = Vec::new();
    while data_files.len() > 0 {
        empty_id = 0;
        let mut last_data = data_files.pop().unwrap();
        while last_data.length > 0 {
            
            let free_data = &mut free_space[empty_id];
            if free_data.start > last_data.start {
                compressed.push(last_data);
                break;
            }
            if free_data.length >= last_data.length {
                let compressed_data = Data{start : free_data.start, length : last_data.length, id : last_data.id};
                free_data.start += last_data.length;
                free_data.length -= last_data.length;
                last_data.length -= last_data.length;
                compressed.push(compressed_data);
            } else {
                empty_id += 1;
            }
        }
    }
    return calc_hash(compressed);
}

fn main() -> std::io::Result<()>{
    let args: Vec<_> = env::args().collect();
    if args.len() <= 1 {
        return Ok(());
    }
    let mut file = File::open(args[1].clone())?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    contents = contents.trim().to_string();
    let char_vec : Vec<u32> = contents.chars().map(|c| c.to_digit(10).unwrap()).collect();
    let mut free : bool = false;
    let mut data_files : Vec<Data> = Vec::new();
    let mut free_space : Vec<Data> = Vec::new();
    let mut id : i64 = 0;
    let mut pos : i64 = 0;
    for c in char_vec {
        let val = c as i64;
        if free {
            free_space.push(Data{start:pos, length:val, id:-1});
        } else {
            data_files.push(Data{start:pos, length:val, id:id});
            id += 1;
        }
        pos += val;
        free = !free;
    }
    let ans_a : i64 = compress(data_files.clone(), free_space.clone());
    let ans_b : i64 = compress_b(data_files.clone(), free_space.clone());
    
    println!("Answer part A: {}", ans_a);
    println!("Anwer part B: {}", ans_b);
    Ok(())
}
