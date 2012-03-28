class Classbj < ActiveRecord::Base
  validates :name, :presence => true, :uniqueness => true
  belongs_to :department
  has_many :students

  def avg_score
    return 0 if self.num == 0
    self.score / self.num
  end

  def rank_department
    Classbj.where("department_id = :dpt AND score > :s", 
                  dpt: self.department, s: self.score).count + 1
  end

  def rank_global
    Classbj.where("score > #{self.score}").count + 1
  end
end
