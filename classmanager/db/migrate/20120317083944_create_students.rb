class CreateStudents < ActiveRecord::Migration
  def change
    create_table :students do |t|
      t.string :name
      t.string :sex
      t.string :No
      t.references :classbj

      t.timestamps
    end
  end
end
