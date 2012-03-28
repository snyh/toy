class Student < ActiveRecord::Base
  validates :No, :presence => true, :uniqueness => true
  belongs_to :classbj
  has_many :events

  after_create do |s|
    self.classbj.num += 1
    self.classbj.save
  end

  def score
    self.events.all.sum { |x| x.regulation.score }
  end

  def week_score
    self.events.where("date > 0").sum { |x| x.regulation.score }
  end
end
