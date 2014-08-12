template <class T>
class Matrix {
public:
    Matrix();
    Matrix(int rows, int columns);
    Matrix(const Matrix<T> &other);
    Matrix<T> & operator= (const Matrix<T> &other);
    ~Matrix();
    void resize(int rows, int columns);
    void clear(void);
    T& operator () (int x, int y);
    inline int minsize(void) { return ((m_rows < m_columns) ? m_rows : m_columns); }
    inline int columns(void) { return m_columns; }
    inline int rows(void) { return m_rows; }
private:
    T **m_matrix;
    int m_rows;
    int m_columns;
};

template <class T>
Matrix<T>::Matrix() {
    m_rows = 0;
    m_columns = 0;
    m_matrix = NULL;
}

template <class T>
Matrix<T>::Matrix(const Matrix<T> &other) {
    if(other.m_matrix != NULL ) {
        m_matrix = NULL;
        resize(other.m_rows, other.m_columns);
        for(int i = 0 ; i < m_rows ; i++ )
            for(int j = 0 ; j < m_columns ; j++ )
                m_matrix[i][j] = other.m_matrix[i][j];
    } else {
        m_matrix = NULL;
        m_rows = 0;
        m_columns = 0;
    }
}

template <class T>
Matrix<T>::Matrix(int rows, int columns) {
    m_matrix = NULL;
    resize(rows, columns);
}

template <class T>
Matrix<T> &
Matrix<T>::operator=(const Matrix<T> &other) {
    if(other.m_matrix != NULL ) {
        resize(other.m_rows, other.m_columns);
        for(int i = 0 ; i < m_rows ; i++ )
            for(int j = 0 ; j < m_columns ; j++ )
                m_matrix[i][j] = other.m_matrix[i][j];
    } else {
        for(int i = 0 ; i < m_columns ; i++ )
            delete [] m_matrix[i];
        delete [] m_matrix;
        m_matrix = NULL;
        m_rows = 0;
        m_columns = 0;
    }
    return *this;
}

template <class T>
Matrix<T>::~Matrix() {
    if(m_matrix != NULL ) {
        for(int i = 0 ; i < m_rows ; i++ )
            delete [] m_matrix[i];
        delete [] m_matrix;
    }
    m_matrix = NULL;
}

template <class T>
void Matrix<T>::resize(int rows, int columns) {
    if(m_matrix == NULL ) {
        m_matrix = new T*[rows];
        for(int i = 0 ; i < rows ; i++ )
            m_matrix[i] = new T[columns];

        m_rows = rows;
        m_columns = columns;
        clear();
    } else {
        T **new_matrix;
        new_matrix = new T*[rows];
        for(int i = 0 ; i < rows ; i++ ) {
            new_matrix[i] = new T[columns];
            for(int j = 0 ; j < columns ; j++ )
                new_matrix[i][j] = 0;
        }
        int minrows = std::min<int>(rows, m_rows);
        int mincols = std::min<int>(columns, m_columns);
        for(int x = 0 ; x < minrows ; x++ )
            for(int y = 0 ; y < mincols ; y++ )
                new_matrix[x][y] = m_matrix[x][y];
        if(m_matrix != NULL ) {
            for(int i = 0 ; i < m_rows ; i++ )
                delete [] m_matrix[i];

            delete [] m_matrix;
        }
        m_matrix = new_matrix;
    }
    m_rows = rows;
    m_columns = columns;
}

template <class T>
void Matrix<T>::clear() {
    for(int i = 0 ; i < m_rows ; i++ )
        for(int j = 0 ; j < m_columns ; j++ )
            m_matrix[i][j] = 0;
}

template <class T>
inline T& Matrix<T>::operator ()(int x, int y) {
    return m_matrix[x][y];
}

#include <list>

class Munkres {
public:
    void solve(Matrix<double> &m);
private:
    static const int NORMAL = 0;
    static const int STAR = 1;
    static const int PRIME = 2; 
    inline bool find_uncovered_in_matrix(double,int&,int&);
    inline bool pair_in_list(const std::pair<int,int> &, const std::list<std::pair<int,int> > &);
    int step1(void);
    int step2(void);
    int step3(void);
    int step4(void);
    int step5(void);
    int step6(void);
    Matrix<int> mask_matrix;
    Matrix<double> matrix;
    bool *row_mask;
    bool *col_mask;
    int saverow, savecol;
};

bool Munkres::find_uncovered_in_matrix(double item, int &row, int &col) {
  for(row = 0 ; row < matrix.rows() ; row++ )
    if(!row_mask[row] )
      for(col = 0 ; col < matrix.columns() ; col++ )
        if(!col_mask[col] )
          if(matrix(row,col) == item )
            return true;
  return false;
}

bool Munkres::pair_in_list(const std::pair<int,int> &needle, const std::list<std::pair<int,int> > &haystack) {
  for(std::list<std::pair<int,int> >::const_iterator i = haystack.begin() ; i != haystack.end() ; i++ )
    if(needle == *i )
      return true;
  return false;
}

int Munkres::step1(void) {
  for(int row = 0 ; row < matrix.rows() ; row++ )
    for(int col = 0 ; col < matrix.columns() ; col++ )
      if(matrix(row,col) == 0 ) {
        bool isstarred = false;
        for(int nrow = 0 ; nrow < matrix.rows() ; nrow++ )
          if(mask_matrix(nrow,col) == STAR ) {
            isstarred = true;
            break;
          }
        if(!isstarred ) {
          for(int ncol = 0 ; ncol < matrix.columns() ; ncol++ )
            if(mask_matrix(row,ncol) == STAR ) {
              isstarred = true;
              break;
            }
        }
        if(!isstarred )
          mask_matrix(row,col) = STAR;
      }
  return 2;
}

int Munkres::step2(void) {
  int rows = matrix.rows();
  int cols = matrix.columns();
  int covercount = 0;
  for(int row = 0 ; row < rows ; row++ )
    for(int col = 0 ; col < cols ; col++ )
      if(mask_matrix(row,col) == STAR ) {
        col_mask[col] = true;
        covercount++;
      }
  int k = matrix.minsize();
  if(covercount >= k ) {
    return 0;
  }
  return 3;
}

int Munkres::step3(void) {
  if(find_uncovered_in_matrix(0, saverow, savecol) )
    mask_matrix(saverow,savecol) = PRIME; 
  else
    return 5;
  for(int ncol = 0 ; ncol < matrix.columns() ; ncol++ )
    if(mask_matrix(saverow,ncol) == STAR ) {
      row_mask[saverow] = true; 
      col_mask[ncol] = false; 
      return 3; 
    }
  return 4; 
}

int Munkres::step4(void) {
  int rows = matrix.rows();
  int cols = matrix.columns();
  std::list<std::pair<int,int> > seq;
  std::pair<int,int> z0(saverow, savecol);
  std::pair<int,int> z1(-1,-1);
  std::pair<int,int> z2n(-1,-1);
  seq.insert(seq.end(), z0);
  int row, col = savecol;
  bool madepair;
  do {
    madepair = false;
    for(row = 0 ; row < rows ; row++ )
      if(mask_matrix(row,col) == STAR ) {
        z1.first = row;
        z1.second = col;
        if(pair_in_list(z1, seq) )
          continue;
        madepair = true;
        seq.insert(seq.end(), z1);
        break;
      }
    if(!madepair )
      break;
    madepair = false;
    for(col = 0 ; col < cols ; col++ )
      if(mask_matrix(row,col) == PRIME ) {
        z2n.first = row;
        z2n.second = col;
        if(pair_in_list(z2n, seq) )
          continue;
        madepair = true;
        seq.insert(seq.end(), z2n);
        break;
      }
  } while(madepair );
  for(std::list<std::pair<int,int> >::iterator i = seq.begin() ;
      i != seq.end() ;
      i++ ) {
    if(mask_matrix(i->first,i->second) == STAR )
      mask_matrix(i->first,i->second) = NORMAL;
    if(mask_matrix(i->first,i->second) == PRIME )
      mask_matrix(i->first,i->second) = STAR;
  }
  for(int row = 0 ; row < mask_matrix.rows() ; row++ )
    for(int col = 0 ; col < mask_matrix.columns() ; col++ )
      if(mask_matrix(row,col) == PRIME )
        mask_matrix(row,col) = NORMAL;
  for(int i = 0 ; i < rows ; i++ ) {
    row_mask[i] = false;
  }
  for(int i = 0 ; i < cols ; i++ ) {
    col_mask[i] = false;
  }
  return 2;
}

int Munkres::step5(void) {
  int rows = matrix.rows();
  int cols = matrix.columns();
  double h = 0;
  for(int row = 0 ; row < rows ; row++ ) {
    if(!row_mask[row] ) {
      for(int col = 0 ; col < cols ; col++ ) {
        if(!col_mask[col] ) {
          if((h > matrix(row,col) && matrix(row,col) != 0) || h == 0 ) {
            h = matrix(row,col);
          }
        }
      }
    }
  }
  for(int row = 0 ; row < rows ; row++ )
    if(row_mask[row] )
      for(int col = 0 ; col < cols ; col++ )
        matrix(row,col) += h;
  for(int col = 0 ; col < cols ; col++ )
    if(!col_mask[col] )
      for(int row = 0 ; row < rows ; row++ )
        matrix(row,col) -= h;
  return 3;
}

void Munkres::solve(Matrix<double> &m) {
  double highValue = 0;
  for(int row = 0 ; row < m.rows() ; row++ ) {
    for(int col = 0 ; col < m.columns() ; col++ ) {
      if(m(row,col) != INFINITY && m(row,col) > highValue )
        highValue = m(row,col);
    }
  }
  highValue++;
  for(int row = 0 ; row < m.rows() ; row++ )
    for(int col = 0 ; col < m.columns() ; col++ )
      if(m(row,col) == INFINITY )
        m(row,col) = highValue;
  bool notdone = true;
  int step = 1;
  this->matrix = m;
  mask_matrix.resize(matrix.rows(), matrix.columns());
  row_mask = new bool[matrix.rows()];
  col_mask = new bool[matrix.columns()];
  for(int i = 0 ; i < matrix.rows() ; i++ ) {
    row_mask[i] = false;
  }
  for(int i = 0 ; i < matrix.columns() ; i++ ) {
    col_mask[i] = false;
  }
  while(notdone ) {
    switch ( step ) {
      case 0:
        notdone = false;
        break;
      case 1:
        step = step1();
        break;
      case 2:
        step = step2();
        break;
      case 3:
        step = step3();
        break;
      case 4:
        step = step4();
        break;
      case 5:
        step = step5();
        break;
    }
  }
  for(int row = 0 ; row < matrix.rows() ; row++ )
    for(int col = 0 ; col < matrix.columns() ; col++ )
      if(mask_matrix(row,col) == STAR )
        matrix(row,col) = 0;
      else
        matrix(row,col) = -1;
  m = matrix;
  delete [] row_mask;
  delete [] col_mask;
}