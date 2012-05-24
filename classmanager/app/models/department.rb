class Department < ActiveRecord::Base
  validates :name, :presence => true, :uniqueness => true

  def num_of_class
    return self.classes.length
  end

  def avg_score
    return 0 if self.num_of_class <= 0
    self.score / self.num_of_class
  end

  def score
    self.classes.sum {|x| x.avg_score}
  end

  def classes
    return Classbj.where("department_id == #{self.id}")
  end

end
