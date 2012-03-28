#encoding:utf-8
class Event < ActiveRecord::Base
  belongs_to :student
  belongs_to :regulation
  
  after_create do |e|
    c = e.student.classbj
    c.score += e.score!
    c.save
  end

  def description
    self.regulation.name
  end

  def score!
    self.regulation.score
  end 

  def score
    self.regulation.score.abs
  end

  def type
    if regulation.score > 0 
      return true
    else
      return false
    end
  end
end
