fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut io = cp::io::default();
    let t: usize = io.read()?;
    for _ in 0..t {
        let mut v: Vec<u8> = io.read_vec(3)?;
        v.sort();
        if v.len() == 3 && v[1] + v[2] >= 10 {
            io.print("YES")?;
        } else {
            io.print("NO")?;
        }
    }

    Ok(())
}

#[cfg(sdm)]
#[allow(dead_code)]
#[path = "../../lib/cp"]
mod cp {
    pub mod io;
}
