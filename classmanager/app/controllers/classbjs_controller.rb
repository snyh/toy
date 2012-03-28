class ClassbjsController < ApplicationController
  def show
    c = Classbj.find(params[:id])
    @students = c.students
    @classname = c.name
    @departname = c.department.name
    @departurl = department_path(c.department)

    @global_rank = c.rank_global
    @depart_rank = c.rank_department

    @score = c.score
    @avg_score = c.avg_score
  end
end
