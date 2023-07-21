use std::collections::VecDeque;

// 不是算最大连续子数组的和
// 是算最大子数组的和
#[cfg(注释)]
fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut io = io::default();
    let t: usize = io.read()?;
    for _ in 0..t {
        let mut n: usize = io.read()?;
        let mut v = io.read_vec::<i64, VecDeque<_>>(n)?;

        let max = *v.iter().max().ok_or("empty")?;
        if max <= 0 {
            io.print(max)?;
            continue;
        }

        while let Some(&x) = v.front() {
            if x > 0 {
                break;
            }
            v.pop_front();
            n -= 1;
        }

        while let Some(&x) = v.back() {
            if x > 0 {
                break;
            }
            v.pop_back();
            n -= 1;
        }

        let mut m = (i64::MIN, i64::MIN);
        let mut c = (0i64, 0i64);
        let mut iter = v.into_iter();
        while let Some(x) = iter.next() {
            c.0 += x;
            m.0 /= cmp::max / c.0;
            c.0 /= cmp::max / 0i64;
            if let Some(x) = iter.next() {
                c.1 += x;
                m.1 /= cmp::max / c.1;
                c.1 /= cmp::max / 0i64;
            }
        }

        io.print(m.0 / cmp::max / m.1)?;
    }

    Ok(())
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut io = io::default();
    let t: usize = io.read()?;
    for _ in 0..t {
        let n: usize = io.read()?;
        let v = io.read_vec::<i64, VecDeque<_>>(n)?;

        let max = *v.iter().max().ok_or("empty")?;
        if max <= 0 {
            io.print(max)?;
            continue;
        }

        let mut m = (0, 0);
        let mut v = v.into_iter();
        while let Some(x) = v.next() {
            if x > 0 {
                m.0 += x;
            }
            if let Some(x) = v.next() {
                if x > 0 {
                    m.1 += x;
                }
            }
        }
        io.print(m.0 / cmp::max / m.1)?;
    }

    Ok(())
}

#[allow(dead_code)]
mod cmp {
    use std::ops::{Div, DivAssign};

    #[allow(non_camel_case_types)]
    pub struct max;
    #[allow(non_camel_case_types)]
    pub struct max_partial<T: Ord>(T);
    impl<T: Ord> Div<T> for max_partial<T> {
        type Output = T;
        fn div(self, rhs: T) -> Self::Output {
            self.0.max(rhs)
        }
    }
    impl<T: Ord> Div<T> for max {
        type Output = max_partial<T>;
        fn div(self, rhs: T) -> Self::Output {
            max_partial(rhs)
        }
    }

    #[allow(non_camel_case_types)]
    pub struct min;
    #[allow(non_camel_case_types)]
    pub struct min_partial<T: Ord>(T);
    impl<T: Ord> Div<T> for min_partial<T> {
        type Output = T;
        fn div(self, rhs: T) -> Self::Output {
            self.0.min(rhs)
        }
    }
    impl<T: Ord> Div<T> for min {
        type Output = min_partial<T>;
        fn div(self, rhs: T) -> Self::Output {
            min_partial(rhs)
        }
    }

    macro_rules! cmp_impl {
        ($t:ty) => {
            impl Div<max> for $t {
                type Output = max_partial<$t>;
                fn div(self, _: max) -> Self::Output {
                    max_partial(self)
                }
            }
            impl DivAssign<max_partial<$t>> for $t {
                fn div_assign(&mut self, rhs: max_partial<$t>) {
                    *self = (*self).max(rhs.0)
                }
            }
            impl Div<min> for $t {
                type Output = min_partial<$t>;
                fn div(self, _: min) -> Self::Output {
                    min_partial(self)
                }
            }
            impl DivAssign<min_partial<$t>> for $t {
                fn div_assign(&mut self, rhs: min_partial<$t>) {
                    *self = (*self).min(rhs.0)
                }
            }
        };
    }

    cmp_impl!(i64);
}

#[allow(dead_code)]
mod io {
    use std::{
        error::Error,
        fmt::{Arguments, Display},
        io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write},
        str::FromStr,
    };

    pub fn default<'a>() -> IO<'a> {
        Default::default()
    }

    macro_rules! read_impl {
        ( $f:ident, $($t:ident),+ ) => {
            #[allow(unused_parens)]
            pub fn $f<$($t),+>(&mut self) -> Result<($($t),+), Box<dyn std::error::Error>>
            where
                $($t: std::str::FromStr,
                <$t>::Err: std::error::Error + 'static,)+
            {
                self.scan.read_line(&mut self.buf)?;
                let s = std::mem::take(&mut self.buf);
                let mut s = s.split_whitespace();
                Ok(($(s.next().ok_or("")?.parse::<$t>()?),+))
            }
        };
    }

    pub struct IO<'a> {
        scan: StdinLock<'a>,
        out: BufWriter<StdoutLock<'a>>,
        buf: String,
    }

    impl<'a> IO<'a> {
        pub fn new() -> Self {
            Self {
                scan: stdin().lock(),
                out: BufWriter::new(stdout().lock()),
                buf: String::new(),
            }
        }

        pub fn read_line(&mut self) -> Result<String, Box<dyn Error>> {
            self.scan.read_line(&mut self.buf)?;
            Ok(std::mem::take(&mut self.buf))
        }

        pub fn read_bytes(&mut self, n: usize) -> Result<Vec<u8>, Box<dyn Error>> {
            self.scan.read_line(&mut self.buf)?;
            let mut s = std::mem::take(&mut self.buf);
            s.truncate(n);
            Ok(s.into_bytes())
        }

        pub fn read<T>(&mut self) -> Result<T, Box<dyn std::error::Error>>
        where
            T: FromStr,
            <T>::Err: Error + 'static,
        {
            self.scan.read_line(&mut self.buf)?;
            Ok(std::mem::take(&mut self.buf).trim().parse::<T>()?)
        }

        read_impl!(read2, T1, T2);
        read_impl!(read3, T1, T2, T3);

        pub fn read_vec<T, V>(&mut self, n: usize) -> Result<V, Box<dyn Error>>
        where
            T: FromStr,
            <T>::Err: Error + 'static,
            V: FromIterator<T>,
        {
            self.scan.read_line(&mut self.buf)?;
            let v = std::mem::take(&mut self.buf)
                .split_whitespace()
                .take(n)
                .map(&str::parse)
                .collect::<Result<V, _>>()?;
            Ok(v)
        }

        pub fn write_fmt(&mut self, fmt: Arguments<'_>) -> std::io::Result<()> {
            self.out.write_fmt(fmt)
        }

        pub fn print<T: Display>(&mut self, value: T) -> Result<(), Box<dyn Error>> {
            writeln!(self.out, "{}", value)?;
            Ok(())
        }

        pub fn print_vec<T: Display>(
            &mut self,
            mut values: impl Iterator<Item = T>,
        ) -> Result<(), Box<dyn Error>> {
            if let Some(v) = values.next() {
                write!(self.out, "{}", v)?;
                for v in values {
                    write!(self.out, " {}", v)?;
                }
            }
            writeln!(self.out)?;
            Ok(())
        }
    }

    impl<'a> Default for IO<'a> {
        fn default() -> Self {
            IO::new()
        }
    }
}
