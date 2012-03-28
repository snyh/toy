#encoding:utf-8
class StudentsController < ApplicationController
  def show
    s = Student.find(params[:id])
    @classname = s.classbj.name
    @classurl = classbj_path(s.classbj)
    @departname = s.classbj.department.name
    @departurl = department_path(s.classbj.department)
    @studentname = s.name

    @score = s.score

    @global_rank = 14
    @depart_rank = 5

    @events = s.events.order("date DESC")
    @chart_month = self.month
    @chart_year = self.year
  end

  protected
  def week_score(year, month, day)
    s_add = []
    s_minus = []
    tmp1 = 0
    tmp2 = 0
    @events.where("date <= :day", day: Date.new(year, month, 1)).each do |e|
      if e.score! > 0
        #tmp1 += e.score
      else
        #tmp2 += e.score
      end
    end
    (1..day).each do |d|
      d = Date.new(year, month, d)
      es = @events.where("date >= :b AND date <= :day", b: d, day: d.succ)
      es.each do |e|
        if e.score! > 0
          tmp1 += e.score
        else
          tmp2 += e.score
        end
      end
      s_add.push(tmp1)
      s_minus.push(tmp2)
    end
    s_avg = s_add.zip(s_minus).map {|x| x[0]-x[1]}
    return [s_add, s_minus, s_avg]
  end
  def month_score(year, month)
    tmp = []
    (1..month).each do |m| 
      s = week_score(year, m, 28)
      tmp.push [s[0][-1], s[1][-1], s[2][-1]]
    end
    xx = [[],[],[]]
    tmp.each do |m|
      xx[0].push m[0]
      xx[1].push m[1]
      xx[2].push m[2]
    end
    return xx
  end

  def month
    LazyHighCharts::HighChart.new('graph') do |f|
      f.title({:text => "本月趋势图"})
      f.options[:xAxis][:categories] = (1..31).map {|x| x.to_s }
      f.options[:chart][:defaultSeriesType] = "area"
      today = Date.today
      s_add, s_minus, s_avg = week_score(today.year, today.month, today.day)
      f.series(:name=>'加分', :data=>s_add)
      f.series(:name=>'减分', :data=>s_minus)
      f.series(:name=>'平均', :type=>'spline', :data=>s_avg)
    end
  end

  def year
    LazyHighCharts::HighChart.new('graph') do |f|
      f.title({ :text=>"年度趋势图"})
      f.options[:xAxis][:categories] = ['一月', '二月', '三月', '四月', '五月','六月', 
        '七月', '八月', '九月', '十月', '十一月','十二月']
      today = Date.today
      s_add, s_minus, s_avg = month_score(today.year, today.month)
      f.series(:type=> 'column',:name=> '加分',:data=> s_add)
      f.series(:type=> 'column',:name=> '减分',:data=> s_minus)
      f.series(:type=> 'spline',:name=> '平均', :data=> s_avg)
    end
  end
end
